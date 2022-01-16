//===============================================
#include "GXml.h"
#include "GString.h"
#include "GLog.h"
//===============================================
GXml* GXml::m_instance = 0;
//===============================================
GXml::GXml() : GObject() {
    m_node = 0;
    m_doc = 0;
    m_xpath = 0;
    m_xpathObj = 0;

    xmlKeepBlanksDefault(0);
}
//===============================================
GXml::~GXml() {
    xmlXPathFreeObject(m_xpathObj);
    xmlXPathFreeContext(m_xpath);
    xmlFreeDoc(m_doc);
}
//===============================================
GXml* GXml::Instance() {
    if(m_instance == 0) {
        m_instance = new GXml;
    }
    return m_instance;
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
GXml& GXml::loadXmlFile(const std::string& _filename) {
    m_doc = xmlReadFile(_filename.c_str(), 0, 0);
    if(!m_doc) {
        GLOG->addError(sformat("Erreur la methode (loadXmlFile) a echoue "
                "sur le fichier (%s).", _filename.c_str()));
    }
    m_filename = _filename;
    return *this;
}
//===============================================
GXml& GXml::loadXmlData(const std::string& _data) {
    m_doc = xmlParseDoc(BAD_CAST(_data.c_str()));
    if(!m_doc) {
        GLOG->addError(sformat("Erreur la methode (loadXmlData) a echoue "
                "sur la source (%s).", _data.c_str()));
    }
    return *this;
}
//===============================================
GXml& GXml::saveXmlFile(const std::string& _filename, const std::string& _encoding, int _format) {
    std::string lFilename = "";

    if(_filename != "") {
        lFilename = _filename;
    }
    else if(m_filename != "") {
        lFilename = m_filename;
    }
    else {
        return *this;
    }

    xmlSaveFormatFileEnc(lFilename.c_str(), m_doc, _encoding.c_str(), _format);
    return *this;
}
//===============================================
GXml& GXml::createDoc(const std::string& _version) {
    m_doc = xmlNewDoc(BAD_CAST(_version.c_str()));
    return *this;
}
//===============================================
GXml& GXml::createRoot(const std::string& _nodename) {
    m_node = xmlNewNode(0, BAD_CAST(_nodename.c_str()));
    xmlDocSetRootElement(m_doc, m_node);
    return *this;
}
//===============================================
GXml& GXml::getRoot(const std::string& _nodename) {
    m_node = xmlDocGetRootElement(m_doc);
    if(!m_node) {
        GLOG->addError(sformat("Erreur la methode (getRoot) a echoue "
                "sur le noeud (%s) (1).", _nodename.c_str()));
        return *this;
    }
    std::string lNodeName = (char*)m_node->name;
    if(lNodeName != _nodename) {
        GLOG->addError(sformat("Erreur la methode (getRoot) a echoue "
                "sur le noeud (%s) (2).", _nodename.c_str()));
    }
    return *this;
}
//===============================================
GXml& GXml::createNode(const std::string& _nodename) {
    m_node = xmlNewNode(NULL, BAD_CAST(_nodename.c_str()));
    return *this;
}
//===============================================
GXml& GXml::createNodePath(const std::string& _path) {
    if(!m_doc) {
        return *this;
    }
    std::vector<std::string> lPaths = GString(_path).splitData('/');
    std::string lName = "";
    m_node = xmlDocGetRootElement(m_doc);
    for(size_t i = 0; i < lPaths.size(); i++) {
        std::string lPath = GString(lPaths.at(i)).trimData();
        if(lPath == "") continue;
        lName += "/" + lPath;
        int lCount = queryXPath(lName).countXPath();
        if(!lCount) {
            GXml lDom;
            lDom.createNode(lPath);
            appendNode(lDom);
        }
        getNode(lPath);
    }
    return *this;
}
//===============================================
GXml& GXml::createNodeFromString(const std::string& _value) {
    if(!m_node) {
        return *this;
    }
    xmlNodePtr lNewNode;
    std::string lData = "<rdv>" + _value + "</rdv>";
    xmlParseInNodeContext(m_node, lData.c_str(), lData.length(), 0, &lNewNode);
    xmlNodePtr lNode = lNewNode->children;
     while(lNode) {
         xmlAddChild(m_node, xmlCopyNode(lNode, 1));
         lNode = lNode->next;
     }
     xmlFreeNode(lNewNode);
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
GXml& GXml::createNodeValue(const std::string& _nodename, const std::string& _value) {
    createNode(_nodename);
    setNodeValue(_value);
    return *this;
}
//===============================================
GXml& GXml::setNodeValue(const std::string& _value) {
    if(!m_node) {
        return *this;
    }
    xmlNodeSetContent(m_node, BAD_CAST(_value.c_str()));
    return *this;
}
//===============================================
GXml& GXml::setNodeCData(const std::string& _value) {
    if(!m_node) {
        return *this;
    }
    GXml lNode;
    lNode.createNode((char*)m_node->name);
    lNode.appendCData(_value);
    replaceNode(lNode);
    return *this;
}
//===============================================
GXml& GXml::appendNode(GXml& _xml) {
    if(!m_node || !_xml.m_node) {
        return *this;
    }
    xmlAddChild(m_node, _xml.m_node);
    return *this;
}
//===============================================
GXml& GXml::appendNode(const std::string& _nodename) {
    if(!m_node) {
        return *this;
    }
    GXml lNode;
    lNode.createNode(_nodename);
    appendNode(lNode);
    return *this;
}
//===============================================
GXml& GXml::appendNode(const std::string& _nodename, const std::string& _value) {
    if(!m_node) {
        return *this;
    }
    GXml lNode;
    lNode.createNodeValue(_nodename, _value);
    appendNode(lNode);
    return *this;
}
//===============================================
GXml& GXml::appendCData(const std::string& _value) {
    if(!m_node) {
        return *this;
    }
    GXml lCData;
    lCData.createCData(*this, _value);
    appendNode(lCData);
    return *this;
}
//===============================================
GXml& GXml::appendCData(const std::string& _nodename, const std::string& _value) {
    if(!m_node) {
        return *this;
    }
    GXml lNode;
    lNode.createNode(_nodename);
    lNode.appendCData(_value);
    appendNode(lNode);
    return *this;
}
//===============================================
GXml& GXml::replaceNode(GXml& _xml) {
    if(!m_node || !_xml.m_node) {
        return *this;
    }
    xmlReplaceNode(m_node, _xml.m_node);
    xmlFreeNode(m_node);
    return *this;
}
//===============================================
GXml& GXml::copyNode(GXml& _xml) {
    if(!_xml.m_node) {
        return *this;
    }
    m_node = xmlCopyNode(_xml.m_node, 1);
    return *this;
}
//===============================================
GXml& GXml::appendFromNode(GXml& _xml) {
    if(!m_node || !_xml.m_node) {
        return *this;
    }
    GXml lNode;
    lNode.copyNode(_xml);
    appendNode(lNode);
    return *this;
}
//===============================================
GXml& GXml::appendFromNodes(GXml& _xml) {
    for(int i = 0; i < _xml.countXPath(); i++) {
        _xml.getNodeItem(i);
        appendFromNode(_xml);
    }
    return *this;
}
//===============================================
GXml& GXml::getNode(const std::string& _nodename) {
    if(!m_node) {
        return *this;
    }
    xmlNodePtr lNode  = xmlFirstElementChild(m_node);
    while(lNode) {
        std::string lNodeName = (char*)lNode->name;
        if(lNodeName == _nodename) {
            m_node = lNode;
            return *this;
        }
        lNode = xmlNextElementSibling(lNode);
    }
    return *this;
}
//===============================================
std::string GXml::getNodeValue() const {
    if(!m_node) {
        GLOG->addError("Erreur la methode (getNodeValue) a echoue.");
        return "";
    }
    std::string lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
std::string GXml::getNodeString(const std::string& _encoding, int _format) const {
    if(!m_node) {
        return "";
    }
    xmlBufferPtr lBuffer = xmlBufferCreate();
    xmlNodeDump(lBuffer, m_doc, m_node, 0, 1);
    std::string lData = (char*)lBuffer->content;
    xmlBufferFree(lBuffer);
    return lData;
}
//===============================================
GXml& GXml::createXPath() {
    if(!m_doc) {
        return *this;
    }
    m_xpath = xmlXPathNewContext(m_doc);
    return *this;
}
//===============================================
GXml& GXml::queryXPath(const std::string& _query) {
    if(!m_xpath) {
        return *this;
    }
    m_xpathObj = xmlXPathEvalExpression(BAD_CAST(_query.c_str()), m_xpath);
    return *this;
}
//===============================================
int GXml::countXPath() const {
    if(!m_xpathObj) {
        return 0;
    }
    if(!m_xpathObj->nodesetval) {
        return 0;
    }
    int lCount = m_xpathObj->nodesetval->nodeNr;
    return lCount;
}
//===============================================
GXml& GXml::getNodeXPath() {
    if(!m_xpathObj) {
        m_node = 0;
        return *this;
    }
    if(!m_xpathObj->nodesetval) {
        m_node = 0;
        return *this;
    }
    if(!m_xpathObj->nodesetval->nodeNr) {
        m_node = 0;
        return *this;
    }
    m_node = m_xpathObj->nodesetval->nodeTab[0];
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
GXml& GXml::getNodeItem(int _index) {
    if(!m_xpathObj) {
        m_node = 0;
        return *this;
    }
    if(!m_xpathObj->nodesetval) {
        m_node = 0;
        return *this;
    }
    if(!m_xpathObj->nodesetval->nodeNr) {
        m_node = 0;
        return *this;
    }
    m_node = m_xpathObj->nodesetval->nodeTab[_index];
    return *this;
}
//===============================================
std::string GXml::toString(const std::string& _encoding, int _format) const {
    if(!m_doc) {
        return "";
    }
    xmlChar* lBuffer = NULL;
    int lSize;
    xmlDocDumpFormatMemoryEnc(m_doc, &lBuffer, &lSize, _encoding.c_str(), _format);
    std::string lData = (char*)lBuffer;
    xmlFree(lBuffer);
    return lData;
}
//===============================================
