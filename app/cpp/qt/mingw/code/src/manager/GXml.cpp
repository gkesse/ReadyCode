//===============================================
#include "GXml.h"
#include "GLog.h"
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
    xmlCleanupParser();
    xmlMemoryDump();
}
//===============================================
GXml& GXml::loadXmlFile(const std::string& _filename) {
    m_doc = xmlParseFile(_filename.c_str());
    if(!m_doc) {
        GLOG->addError("Erreur la methode (loadXmlFile) a echoue "
                "sur le fichier (%s).", _filename.c_str());
    }
    m_filename = _filename;
    return *this;
}
//===============================================
GXml& GXml::loadXmlData(const std::string& _data) {
    m_doc = xmlParseDoc((xmlChar*)_data.c_str());
    if(!m_doc) {
        GLOG->addError("Erreur la methode (loadXmlData) a echoue "
                "sur la source (%s).", _data.c_str());
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
        GLOG->addError("Erreur la methode (getRoot) a echoue "
                "sur le noeud (%s) (1).", _nodename.c_str());
        return *this;
    }
    std::string lNodeName = (char*)m_node->name;
    if(lNodeName != _nodename) {
        GLOG->addError("Erreur la methode (getRoot) a echoue "
                "sur le noeud (%s) (2).", _nodename.c_str());
    }
    return *this;
}
//===============================================
GXml& GXml::createNode(const std::string& _nodename) {
    m_node = xmlNewNode(NULL, BAD_CAST(_nodename.c_str()));
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
GXml& GXml::replaceNode(GXml& _xml) {
    if(!m_node || !_xml.m_node) {
        return *this;
    }
    xmlReplaceNode(m_node, _xml.m_node);
    xmlFreeNode(m_node);
    return *this;
}
//===============================================
GXml& GXml::getNode(const std::string& _nodename) {
    if(!m_node) {
        GLOG->addError("Erreur la methode (getNode) a echoue "
                "sur le noeud (%s) (1).", _nodename.c_str());
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
    GLOG->addError("Erreur la methode (getNode) a echoue "
            "sur le noeud (%s) (2).", _nodename.c_str());
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
GXml& GXml::queryXPath(const char* _format, ...) {
    if(!m_xpath) {
        return *this;
    }
    va_list lArgs;
    va_start (lArgs, _format);
    int lSize = vsprintf(m_format, _format, lArgs);
    va_end(lArgs);
    if(lSize >= FORMAT_SIZE) {
        GLOG->addError("Erreur la methode (queryXPath) a echoue.");
    }
    m_xpathObj = xmlXPathEvalExpression(BAD_CAST(m_format), m_xpath);
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
std::string GXml::toString() const {
    return toString("UTF-8", 4);
}
//===============================================
std::string GXml::toString(const std::string& _encoding, int _format) const {
    xmlChar* lBuffer = NULL;
    int lSize;
    xmlDocDumpFormatMemoryEnc(m_doc, &lBuffer, &lSize, _encoding.c_str(), _format);
    std::string lData = (char*)lBuffer;
    xmlFree(lBuffer);
    return lData;
}
//===============================================
