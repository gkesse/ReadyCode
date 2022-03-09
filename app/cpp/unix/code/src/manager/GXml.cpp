//===============================================
#include "GXml.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GXml::GXml() {
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
    m_doc = xmlParseFile(_filename.c_str());
    if(!m_doc) {
        GLOG->addError(GFORMAT->sformat("Erreur la methode (loadXmlFile) a echoue "
                "sur le fichier (%s).", _filename.c_str()));
    }
    m_filename = _filename;
    return *this;
}
//===============================================
bool GXml::saveXmlFile(const std::string& _filename, const std::string& _encoding, int _format) {
    std::string lFilename = "";

    if(_filename != "") {
        lFilename = _filename;
    }
    else if(m_filename != "") {
        lFilename = m_filename;
    }
    else {
        GLOG->addError(GFORMAT->sformat("Erreur la methode (saveXmlFile) a echoue "
                "sur le fichier (%s).", lFilename.c_str()));
        return false;
    }

    xmlSaveFormatFileEnc(lFilename.c_str(), m_doc, _encoding.c_str(), _format);
    return true;
}
//===============================================
GXml& GXml::getRoot(const std::string& _nodename) {
    m_node = xmlDocGetRootElement(m_doc);
    if(!m_node) {
        GLOG->addError(GFORMAT->sformat("Erreur la methode (getRoot) a echoue "
                "sur le noeud (%s) (1).", _nodename.c_str()));
        return *this;
    }
    std::string lNodeName = (char*)m_node->name;
    if(lNodeName != _nodename) {
        GLOG->addError(GFORMAT->sformat("Erreur la methode (getRoot) a echoue "
                "sur le noeud (%s) (2).", _nodename.c_str()));
    }
    return *this;
}
//===============================================
GXml& GXml::getNode(const std::string& _nodename) {
    if(!m_node) {
        GLOG->addError(GFORMAT->sformat("Erreur la methode (getNode) a echoue "
                "sur le noeud (%s) (1).", _nodename.c_str()));
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
    GLOG->addError(GFORMAT->sformat("Erreur la methode (getNode) a echoue "
            "sur le noeud (%s) (2).", _nodename.c_str()));
    return *this;
}
//===============================================
std::string GXml::getNodeValue() const {
    if(!m_node) {
        return "";
    }
    std::string lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
GXml& GXml::createNode(const std::string& _nodename) {
    m_node = xmlNewNode(NULL, BAD_CAST(_nodename.c_str()));
    if(!m_node) {
        GLOG->addError(GFORMAT->sformat("Erreur la methode (createNode) a echoue "
                "sur le noeud (%s).", _nodename.c_str()));
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::createNodeValue(const std::string& _nodename, const std::string& _value) {
    createNode(_nodename);
    setNodeValue(_value);
    if(!m_node) {
        GLOG->addError(GFORMAT->sformat("Erreur la methode (createNodeValue) a echoue "
                "sur le noeud (%s) avec la valeur (%s).", _nodename.c_str(), _value.c_str()));
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::setNodeValue(const std::string& _value) {
    if(!m_node) {
        GLOG->addError(GFORMAT->sformat("Erreur la methode (setNodeValue) a echoue "
                "sur le noeud (%s).", _value.c_str()));
        return *this;
    }
    xmlNodeSetContent(m_node, BAD_CAST(_value.c_str()));
    return *this;
}
//===============================================
GXml& GXml::appendNode(GXml& _xml) {
    if(!m_node) {
        GLOG->addError(GFORMAT->sformat("Erreur la methode (appendNode) a echoue."));
        return *this;
    }
    xmlAddChild(m_node, _xml.m_node);
    return *this;
}
//===============================================
GXml& GXml::replaceNode(GXml& _xml) {
    if(!m_node || !_xml.m_node) {
        GLOG->addError(GFORMAT->sformat("Erreur la methode (replaceNode) a echoue."));
        return *this;
    }
    xmlReplaceNode(m_node, _xml.m_node);
    xmlFreeNode(m_node);
    return *this;
}
//===============================================
GXml& GXml::createXPath() {
    if(!m_doc) {
        GLOG->addError(GFORMAT->sformat("Erreur la methode (createXPath) a echoue."));
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
    m_xpathObj = xmlXPathEvalExpression((xmlChar*)_query.c_str(), m_xpath);
    return *this;
}
//===============================================
int GXml::countXPath() const {
    if(!m_xpathObj->nodesetval) {
        return 0;
    }
    if(!m_xpathObj->nodesetval->nodeNr) {
        return 0;
    }
    int lCount = m_xpathObj->nodesetval->nodeNr;
    return lCount;
}
//===============================================
GXml& GXml::getNodeXPath() {
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
    if(!_xml.m_node) {
        GLOG->addError(GFORMAT->sformat("Erreur la methode (createNodeCData) a echoue "
                "sur le noeud (%s) (1).", _value.c_str()));
        return *this;
    }
    m_node = xmlNewCDataBlock(_xml.m_node->doc, BAD_CAST(_value.c_str()), _value.size());
    if(!m_node) {
        GLOG->addError(GFORMAT->sformat("Erreur la methode (createNodeCData) a echoue "
                "sur le noeud (%s) (2).", _value.c_str()));
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
    if(!m_node) {
        GLOG->addError(GFORMAT->sformat("Erreur la methode (setNodeCData) a echoue "
                "sur le noeud (%s).", _value.c_str()));
        return *this;
    }
    GXml lNode;
    lNode.createNodeCData((char*)m_node->name, _value);
    replaceNode(lNode);
    return *this;
}
//===============================================
std::string GXml::getNodeCData() const {
    if(!m_node) {
        return "";
    }
    std::string lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
