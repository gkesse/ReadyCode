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
    m_data = "";
    m_isFile = true;
    m_version = "1.0";
    m_nodeRoot = "rdv";
    xmlKeepBlanksDefault(0);
}
//===============================================
GXml::GXml(const std::string& _data, bool _isFile) : GObject() {
    m_node = 0;
    m_doc = 0;
    m_xpath = 0;
    m_xpathObj = 0;
    m_data = _data;
    m_isFile = _isFile;
    m_version = "1.0";
    m_nodeRoot = "rdv";
    xmlKeepBlanksDefault(0);
    loadXml();
}
//===============================================
GXml::GXml(const std::string& _version, const std::string& _nodeRoot) : GObject() {
    m_node = 0;
    m_doc = 0;
    m_xpath = 0;
    m_xpathObj = 0;
    m_data = "";
    m_isFile = true;
    m_version = _version;
    m_nodeRoot = _nodeRoot;
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
void GXml::loadXml() {
    if(m_data == "") return;
    loadXml(m_data, m_isFile);
}
//===============================================
void GXml::loadXml(const std::string& _data, bool _isFile) {
    if(_data == "") return;
    if(_isFile) {
        try {
            m_doc = xmlParseFile(_data.c_str());
        }
        catch (...) {}
    }
    else {
        try {
            m_doc = xmlParseDoc(BAD_CAST(_data.c_str()));
        }
        catch (...) {}
    }
    createXPath();
}
//===============================================
GXml& GXml::loadXmlData(const std::string& _data) {
    m_doc = xmlParseDoc(BAD_CAST(_data.c_str()));
    if(!m_doc) {
        GERROR_OBJ(eGERR, "Erreur la methode (GXml::loadXmlData) a echoue (1)\n"
                "- source.....: (%s).", _data.c_str());
    }
    return *this;
}
//===============================================
GXml& GXml::saveXmlFile(const std::string& _filename, const std::string& _encoding, int _format) {
    std::string lFilename = "";

    if(_filename != "") {
        lFilename = _filename;
    }
    else if(m_isFile && m_data != "") {
        lFilename = m_data;
    }
    else {
        GERROR_OBJ(eGERR, "Erreur le fichier de sortie n'a pas ete defini.");
        return *this;
    }

    xmlSaveFormatFileEnc(lFilename.c_str(), m_doc, _encoding.c_str(), _format);
    return *this;
}
//===============================================
bool GXml::isValidXml() const {
    if(m_data == "") return false;
    if(!m_doc) return false;
    return true;
}
//===============================================
GXml& GXml::createDoc() {
    if(m_version == "") return *this;
    m_doc = xmlNewDoc(BAD_CAST(m_version.c_str()));
    createRoot();
    createXPath();
    return *this;
}
//===============================================
GXml& GXml::createRoot() {
    if(m_nodeRoot == "") return *this;
    m_node = xmlNewNode(0, BAD_CAST(m_nodeRoot.c_str()));
    xmlDocSetRootElement(m_doc, m_node);
    return *this;
}
//===============================================
GXml& GXml::getRoot() {
    if(!m_doc) return *this;
    if(m_nodeRoot == "") return *this;
    m_node = xmlDocGetRootElement(m_doc);
    if(!m_node) {
        GERROR_OBJ(eGERR, "Erreur le noeud racine n'existe pas.");
        return *this;
    }
    std::string lNodeName = (char*)m_node->name;
    if(lNodeName != m_nodeRoot) {
        GERROR_OBJ(eGERR, "Erreur le noeud racine ne correspond pas.\n"
                "- noeud doc....: (%s)"
                "- noeud arg....: (%s)"
                "", lNodeName.c_str(), m_nodeRoot.c_str());
    }
    return *this;
}
//===============================================
GXml& GXml::getNode(const std::string& _nodename) {
    if(!m_node) return *this;
    xmlNodePtr lNode  = xmlFirstElementChild(m_node);
    while(lNode) {
        std::string lNodeName = (char*)lNode->name;
        if(lNodeName == _nodename) {
            m_node = lNode;
            return *this;
        }
        lNode = xmlNextElementSibling(lNode);
    }
    GERROR_OBJ(eGERR, ""
            "Erreur lors de la lecture du noeud.\n"
            "- noeud........: (%s)"
            "", _nodename.c_str());
    return *this;
}
//===============================================
std::string GXml::getNodeValue() const {
    if(!m_node) return "";
    std::string lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
std::string GXml::getNodeValue(const std::string& _xpath) {
    std::string lData = queryXPath(_xpath).getNodeXPath().getNodeValue();
    return lData;
}
//===============================================
GXml& GXml::createNode(const std::string& _nodename) {
    m_node = xmlNewNode(NULL, BAD_CAST(_nodename.c_str()));
    if(!m_node) {
        GERROR_OBJ(eGERR, "Erreur la methode (GXml::createNode) a echoue (1)\n"
                "- noeud......: (%s)", _nodename.c_str());
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::createNodeValue(const std::string& _nodename, const std::string& _value) {
    createNode(_nodename);
    setNodeValue(_value);
    if(!m_node) {
        GERROR_OBJ(eGERR, "Erreur la methode (GXml::createNodeValue) a echoue (1)\n"
                "- noeud......: (%s)\n"
                "- valeur.....: (%s)", _nodename.c_str(), _value.c_str());
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::createNodePath(const std::string& _path, const std::string& _value) {
    if(!m_doc) {
        return *this;
    }
    std::vector<std::string> lPaths = GString(_path).splitData('/');
    std::string lName = "";
    for(int i = 0; i < lPaths.size(); i++) {
        std::string lPath = GString(lPaths.at(i)).trimData();
        if(lPath == "") continue;
        lName += "/" + lPath;
        int lCount = queryXPath(lName).countXPath();
        if(!lCount) {
            GXml lDom;
            lDom.createNode(lPath);
            appendNode(lDom);
        }
        queryXPath(lName).getNodeXPath();
    }
    if(!_value.empty()) {
        setNodeValue(_value);
    }
    return *this;
}
//===============================================
GXml& GXml::createCData(GXml& _xml, const std::string& _value) {
    if(!_xml.m_node) {
        return *this;
    }
    m_node = xmlNewCDataBlock(_xml.m_node->doc, BAD_CAST(_value.c_str()), _value.size());
    return *this;
}
//===============================================
GXml& GXml::setNodeValue(const std::string& _value) {
    if(!m_node) {
        GERROR_OBJ(eGERR, "Erreur la methode (GXml::setNodeValue) a echoue (1)"
                "- noeud......: (%1)", _value.c_str());
        return *this;
    }
    xmlNodeSetContent(m_node, BAD_CAST(_value.c_str()));
    return *this;
}
//===============================================
GXml& GXml::setNodeValue(const std::string& _key, const std::string& _value) {
    getNode(_key);
    setNodeValue(_value);
    return *this;
}
//===============================================
GXml& GXml::appendNode(GXml& _xml) {
    if(!m_node) return *this;
    xmlAddChild(m_node, _xml.m_node);
    return *this;
}
//===============================================
GXml& GXml::appendNode(const std::string& _nodename) {
    GXml lNode;
    lNode.createNode(_nodename);
    appendNode(lNode);
    return *this;
}
//===============================================
GXml& GXml::appendNode(const std::string& _nodename, const std::string& _value) {
    if(!m_node) return *this;
    GXml lNode;
    lNode.createNodeValue(_nodename, _value);
    appendNode(lNode);
    return *this;
}
//===============================================
GXml& GXml::appendNodeGet(const std::string& _nodename) {
    if(!m_node) return *this;
    GXml lNode;
    lNode.createNode(_nodename);
    appendNode(lNode);
    m_node = lNode.m_node;
    return *this;
}
//===============================================
GXml& GXml::appendNodeGet(const std::string& _nodename, const std::string& _value) {
    if(!m_node) return *this;
    GXml lNode;
    lNode.createNodeValue(_nodename, _value);
    appendNode(lNode);
    m_node = lNode.m_node;
    return *this;
}
//===============================================
GXml& GXml::appendCData(const std::string& _value) {
    if(!m_node) return *this;
    GXml lCData;
    lCData.createCData(*this, _value);
    appendNode(lCData);
    return *this;
}
//===============================================
GXml& GXml::appendCData(const std::string& _nodename, const std::string& _value) {
    if(!m_node) return *this;
    GXml lNode;
    lNode.createNode(_nodename);
    lNode.appendCData(_value);
    appendNode(lNode);
    return *this;
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
GXml& GXml::createXPath() {
    if(!m_doc) return *this;
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {
        GERROR_OBJ(eGERR, "Erreur la creation de l'objet XPath a echoue.");
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::queryXPath(const std::string& _query) {
    if(!m_xpath) return *this;
    m_xpathObj = xmlXPathEvalExpression((xmlChar*)_query.c_str(), m_xpath);
    return *this;
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
GXml& GXml::getNodeXPath() {
    m_node = 0;
    if(!m_xpathObj) return *this;
    if(!m_xpathObj->nodesetval) return *this;
    if(!m_xpathObj->nodesetval->nodeNr) return *this;
    m_node = m_xpathObj->nodesetval->nodeTab[0];
    return *this;
}
//===============================================
GXml& GXml::getNodeItem(int _index) {
    m_node = 0;
    if(!m_xpathObj->nodesetval) return *this;
    if(!m_xpathObj->nodesetval->nodeNr) return *this;
    m_node = m_xpathObj->nodesetval->nodeTab[_index];
    return *this;
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
GXml& GXml::createNodeCData(GXml& _xml, const std::string& _value) {
    if(!_xml.m_node) return *this;
    m_node = xmlNewCDataBlock(_xml.m_node->doc, BAD_CAST(_value.c_str()), _value.size());
    if(!m_node) {
        GERROR_OBJ(eGERR, "Erreur lors de la creation du block CDATA.\n"
                "- noeud......: (%s)", _value.c_str());
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::createNodeCData(const std::string& _nodename, const std::string& _value) {
    createNode(_nodename);
    GXml lNode;
    lNode.createNodeCData(*this, _value);
    appendNode(lNode);
    return *this;
}
//===============================================
GXml& GXml::setNodeCData(const std::string& _value) {
    if(!m_node) return *this;
    GXml lNode;
    lNode.createNodeCData((char*)m_node->name, _value);
    replaceNode(lNode);
    return *this;
}
//===============================================
std::string GXml::getNodeCData() const {
    if(!m_node) return "";
    std::string lData = (char*)xmlNodeGetContent(m_node);
    return lData;
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
