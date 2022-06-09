//===============================================
#include "GXml.h"
#include "GLog.h"
#include "GFormat.h"
#include "GString.h"
#include "GError.h"
//===============================================
GXml::GXml() : GObject() {
    m_node = 0;
    m_doc = 0;
    m_xpath = 0;
    m_xpathObj = 0;
    m_filename = "";
    xmlKeepBlanksDefault(0);
}
//===============================================
GXml::~GXml() {
    xmlXPathFreeObject(m_xpathObj);
    xmlXPathFreeContext(m_xpath);
    xmlFreeDoc(m_doc);
}
//===============================================
void GXml::initModule() {
    xmlInitParser();
}
//===============================================
void GXml::cleanModule() {
    xmlCleanupParser();
    xmlMemoryDump();
}
//===============================================
bool GXml::loadXml(const std::string& _data) {
    std::string lData = GString(_data).trimData();
    if(lData == "") return false;
    m_doc = xmlParseDoc(BAD_CAST(lData.c_str()));
    if(!m_doc) {GERROR(eGERR, "Erreur lors de la création du document."); return false;}
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
bool GXml::loadFile(const std::string& _filename) {
    if(_filename == "") return false;
    m_doc = xmlParseFile(_filename.c_str());
    if(!m_doc) {GERROR(eGERR, "Erreur lors de la création du document."); return false;}
    m_filename = _filename;
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
GXml& GXml::loadNode(const std::string& _data, bool _isRoot) {
    if(!m_node) return *this;
    xmlNodePtr lNewNode;
    std::string lData = _data;
    if(_isRoot) lData = "<rdv>" + _data + "</rdv>";
    xmlParseInNodeContext(m_node, lData.c_str(), lData.size(), 0, &lNewNode);
    xmlNodePtr lNode = lNewNode->children;
    while(lNode) {
        xmlAddChild(m_node, xmlCopyNode(lNode, 1));
        lNode = lNode->next;
    }
    xmlFreeNode(lNewNode);
    return *this;
}
//===============================================
bool GXml::saveXml(const std::string& _filename, const std::string& _encoding, int _format) {
    std::string lFilename = "";
    if(_filename != "") {
        lFilename = _filename;
    }
    else {
        lFilename = m_filename;
    }
    if(lFilename == "") {GERROR(eGERR, "Erreur le nom du fichier est vide."); return false;}
    xmlSaveFormatFileEnc(lFilename.c_str(), m_doc, _encoding.c_str(), _format);
    return true;
}
//===============================================
bool GXml::isValidXml() const {
    if(!m_doc) return false;
    return true;
}
//===============================================
std::string GXml::getNodeValue() const {
    if(!m_node) return "";
    std::string lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
bool GXml::createXNode(const std::string& _path, const std::string& _value, bool _isCData, bool _isGet, bool _isCreate) {
    std::string lPath = GString(_path).trimData();
    if(lPath == "") return false;
    char lChar = lPath[0];
    bool lRootOn = (lChar == '/');
    std::vector<std::string> lMap = GString(lPath).splitData('/');
    lPath = "";

    if(!_isGet) saveNode();

    for(int i = 0; i < (int)lMap.size(); i++) {
        std::string lItem = lMap[i];
        lItem = GString(lItem).trimData();
        if(lItem == "") continue;
        if(lPath != "" || lRootOn) lPath += "/";
        lPath += lItem;
        getXPath(lPath, lRootOn);
        if(countXPath() == 0 || _isCreate) {
            createNode(lItem);
        }
    }
    if(_value != "") {
        setNodeValue(_value, _isCData);
    }

    if(!_isGet) restoreNode();
    return true;
}
//===============================================
bool GXml::createRNode(const std::string& _path, const std::string& _value, bool _isCData) {
    createXNode(_path, _value, _isCData, false);
    return true;
}
//===============================================
bool GXml::createCXNode(const std::string& _path, const std::string& _value, bool _isCData) {
    createXNode(_path, _value, _isCData, true, true);
    return true;
}
//===============================================
bool GXml::createCRNode(const std::string& _path, const std::string& _value, bool _isCData) {
    createXNode(_path, _value, _isCData, false, true);
    return true;
}
//===============================================
bool GXml::createDoc(const std::string& _version) {
    m_doc = xmlNewDoc(BAD_CAST "1.0");
    if(!m_doc) {GERROR(eGERR, "Erreur lors de la création du document."); return false;}
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
bool GXml::createNode(const std::string& _nodename) {
    if(!m_doc) return false;
    xmlNodePtr lNode = xmlNewNode(NULL, BAD_CAST(_nodename.c_str()));
    if(!lNode) GERROR(eGERR, "Erreur lors de la création du noeud.");
    if(!m_node) {
        xmlDocSetRootElement(m_doc, lNode);
    }
    else {
        xmlAddChild(m_node, lNode);
    }
    m_node = lNode;
    return true;
}
//===============================================
bool GXml::setNodeValue(const std::string& _value, bool _isCData) {
    if(!m_doc) return false;
    if(!m_node) return false;
    if(!_isCData) {
        xmlNodeSetContent(m_node, BAD_CAST(_value.c_str()));
    }
    else {
        xmlNodePtr lNode = xmlNewCDataBlock(m_doc, BAD_CAST(_value.c_str()), _value.size());
        if(!lNode) GERROR(eGERR, "Erreur lors de la création du noeud.");
        xmlAddChild(m_node, lNode);
    }
    return true;
}
//===============================================
bool GXml::appendNode(const std::string& _nodename, const std::string& _value, bool _isCData) {
    if(_nodename == "") return false;
    if(!m_node) return false;
    if(!m_doc) return false;
    xmlNodePtr lNode = xmlNewNode(NULL, BAD_CAST(_nodename.c_str()));
    if(_value == "") {
        if(!_isCData) {
            xmlNodeSetContent(lNode, BAD_CAST(_value.c_str()));
        }
        else {
            xmlNodePtr lCData = xmlNewCDataBlock(m_doc, BAD_CAST(_value.c_str()), _value.size());
            xmlAddChild(lNode, lCData);
        }
    }
    xmlAddChild(m_node, lNode);
    return true;
}
//===============================================
GXml& GXml::replaceNode(GXml& _xml) {
    if(!m_node || !_xml.m_node) {
        GERROR_OBJ(eGERR, "Erreur la methode (GXml::replaceNode) a echoue (1)");
        return *this;
    }
    xmlReplaceNode(m_node, _xml.m_node);
    xmlFreeNode(m_node);
    return *this;
}
//===============================================
bool GXml::queryXPath(const std::string& _path, bool _isRoot) {
    if(!m_xpath) return false;
    if(_isRoot) {
        m_xpathObj = xmlXPathEvalExpression(BAD_CAST(_path.c_str()), m_xpath);
    }
    else {
        if(!m_node) return false;
        m_xpathObj = xmlXPathNodeEval(m_node, BAD_CAST(_path.c_str()), m_xpath);
    }
    if(!m_xpathObj) {GERROR(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
bool GXml::getXPath(const std::string& _path, bool _isRoot) {
    if(_path == "") return false;
    queryXPath(_path, _isRoot);
    getNodeXPath();
    return true;
}
//===============================================
int GXml::countXPath() const {
    if(!m_xpathObj) return 0;
    if(!m_xpathObj->nodesetval) return 0;
    if(!m_xpathObj->nodesetval->nodeNr) return 0;
    int lCount = m_xpathObj->nodesetval->nodeNr;
    return lCount;
}
//===============================================
bool GXml::getNodeXPath(int _index) {
    if(!m_xpathObj->nodesetval) return false;
    if(!m_xpathObj->nodesetval->nodeNr) return false;
    m_node = m_xpathObj->nodesetval->nodeTab[_index];
    return true;
}
//===============================================
GXml& GXml::clearNodeXPath() {
    for(int i = 0; i < countXPath(); i++) {
        xmlNodePtr lNode = m_xpathObj->nodesetval->nodeTab[i];
        xmlUnlinkNode(lNode);
        xmlFreeNode(lNode);
    }
    return *this;
}
//===============================================
GXml& GXml::setAttribute(const std::string& _key, const std::string& _value) {
    if(!m_node) return *this;
    xmlSetProp(m_node, BAD_CAST(_key.c_str()), BAD_CAST(_value.c_str()));
    return *this;
}
//===============================================
void GXml::saveNode() {
    m_nodeCopy.push(m_node);
}
//===============================================
void GXml::restoreNode() {
    m_node = m_nodeCopy.top();
    m_nodeCopy.pop();
}
//===============================================
std::string GXml::toString(const std::string& _encoding, int _format) const {
    if(!m_doc) return "";
    xmlChar* lBuffer = NULL;
    int lSize;
    xmlDocDumpFormatMemoryEnc(m_doc, &lBuffer, &lSize, _encoding.c_str(), _format);
    std::string lData = (char*)lBuffer;
    xmlFree(lBuffer);
    return lData;
}
//===============================================
std::string GXml::toStringNode(const std::string& _encoding, int _format) const {
    if(!m_node) return "";
    xmlBufferPtr lBuffer = xmlBufferCreate();
    xmlNodeDump(lBuffer, m_doc, m_node, 0, 1);
    std::string lData = (char*)lBuffer->content;
    xmlBufferFree(lBuffer);
    return lData;
}
//===============================================
