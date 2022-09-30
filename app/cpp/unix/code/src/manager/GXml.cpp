//===============================================
#include "GXml.h"
#include "GLog.h"
#include "GString.h"
//===============================================
GXml::GXml()
: GObject() {
    m_node = 0;
    m_queryNode = 0;
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
bool GXml::loadXml(const GString& _data) {
    GString lData = GString(_data).trim();
    if(lData == "") return false;
    m_doc = xmlParseDoc(BAD_CAST(lData.c_str()));
    if(!m_doc) {GERROR_ADD(eGERR, "Erreur lors de la création du document."); return false;}
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
bool GXml::loadFile(const GString& _filename) {
    if(_filename == "") return false;
    m_doc = xmlParseFile(_filename.c_str());
    if(!m_doc) {GERROR_ADD(eGERR, "Erreur lors de la création du document."); return false;}
    m_filename = _filename;
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
bool GXml::loadNode(const GString& _data, bool _isRoot) {
    if(!m_node) return false;
    xmlNodePtr lNewNode;
    GString lData = _data;
    if(_isRoot) lData = "<rdv>" + _data + "</rdv>";
    xmlParseInNodeContext(m_node, lData.c_str(), lData.size(), 0, &lNewNode);
    xmlNodePtr lNode = lNewNode->children;
    while(lNode) {
        xmlAddChild(m_node, xmlCopyNode(lNode, 1));
        lNode = lNode->next;
    }
    xmlFreeNode(lNewNode);
    return true;
}
//===============================================
bool GXml::saveXml(const GString& _filename, const GString& _encoding, int _format) {
    GString lFilename = "";
    if(_filename != "") {
        lFilename = _filename;
    }
    else {
        lFilename = m_filename;
    }
    if(lFilename == "") {GERROR_ADD(eGERR, "Erreur le nom du fichier est vide."); return false;}
    xmlSaveFormatFileEnc(lFilename.c_str(), m_doc, _encoding.c_str(), _format);
    return true;
}
//===============================================
bool GXml::isValidXml() const {
    if(!m_doc) return false;
    return true;
}
//===============================================
GString GXml::getNodeValue() const {
    if(!countXPath()) return "";
    GString lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
bool GXml::createXNode(const GString& _path, const GString& _value, bool _isCData) {
    GString lPath = GString(_path).trim();
    if(lPath == "") return false;
    char lChar = lPath[0];
    bool lRootOn = (lChar == '/');
    std::vector<GString> lMap = GString(lPath).split("/");
    lPath = "";

    m_queryNode = m_node;

    for(int i = 0; i < (int)lMap.size(); i++) {
        GString lItem = lMap[i];
        lItem = GString(lItem).trim();
        if(lItem == "") continue;
        if(lPath != "" || lRootOn) lPath += "/";
        lPath += lItem;
        getXPath(lPath, lRootOn);
        if(countXPath() == 0) {
            createNode(lItem);
        }
    }
    if(_value != "") {
        setNodeValue(_value, _isCData);
    }
    m_queryNode = 0;
    return true;
}
//===============================================
bool GXml::createDoc(const GString& _version) {
    m_doc = xmlNewDoc(BAD_CAST "1.0");
    if(!m_doc) {GERROR_ADD(eGERR, "Erreur lors de la création du document."); return false;}
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
bool GXml::createNode(const GString& _nodename) {
    if(!m_doc) return false;
    xmlNodePtr lNode = xmlNewNode(NULL, BAD_CAST(_nodename.c_str()));
    if(!lNode) GERROR_ADD(eGERR, "Erreur lors de la création du noeud.");
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
bool GXml::setNodeValue(const GString& _value, bool _isCData) {
    if(!m_doc) return false;
    if(!m_node) return false;
    if(!_isCData) {
        xmlNodeSetContent(m_node, BAD_CAST(_value.c_str()));
    }
    else {
        xmlNodePtr lNode = xmlNewCDataBlock(m_doc, BAD_CAST(_value.c_str()), _value.size());
        if(!lNode) GERROR_ADD(eGERR, "Erreur lors de la création du noeud.");
        xmlAddChild(m_node, lNode);
    }
    return true;
}
//===============================================
bool GXml::queryXPath(const GString& _path, bool _isRoot) {
    if(!m_xpath) return false;
    if(_isRoot) {
        m_xpathObj = xmlXPathEvalExpression(BAD_CAST(_path.c_str()), m_xpath);
    }
    else {
        if(m_queryNode) {
            m_xpathObj = xmlXPathNodeEval(m_queryNode, BAD_CAST(_path.c_str()), m_xpath);
        }
        else {
            m_xpathObj = xmlXPathEvalExpression(BAD_CAST(_path.c_str()), m_xpath);
        }
    }
    if(!m_xpathObj) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
bool GXml::getXPath(const GString& _path, bool _isRoot) {
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
bool GXml::clearXNode() {
    for(int i = 0; i < countXPath(); i++) {
        xmlNodePtr lNode = m_xpathObj->nodesetval->nodeTab[i];
        xmlUnlinkNode(lNode);
        xmlFreeNode(lNode);
    }
    return true;
}
//===============================================
bool GXml::setAttribute(const GString& _key, const GString& _value) {
    if(!m_node) return false;
    xmlSetProp(m_node, BAD_CAST(_key.c_str()), BAD_CAST(_value.c_str()));
    return true;
}
//===============================================
bool GXml::saveNode() {
    m_nodeCopy.push(m_node);
    return true;
}
//===============================================
bool GXml::restoreNode() {
    m_node = m_nodeCopy.top();
    m_nodeCopy.pop();
    return true;
}
//===============================================
GString GXml::toString(const GString& _encoding, int _format) const {
    if(!m_doc) return "";
    xmlChar* lBuffer = NULL;
    int lSize;
    xmlDocDumpFormatMemoryEnc(m_doc, &lBuffer, &lSize, _encoding.c_str(), _format);
    GString lData = (char*)lBuffer;
    xmlFree(lBuffer);
    return lData;
}
//===============================================
GString GXml::toStringNode(const GString& _encoding, int _format) const {
    if(!m_node) return "";
    xmlBufferPtr lBuffer = xmlBufferCreate();
    xmlNodeDump(lBuffer, m_doc, m_node, 0, 1);
    GString lData = (char*)lBuffer->content;
    xmlBufferFree(lBuffer);
    return lData;
}
//===============================================
