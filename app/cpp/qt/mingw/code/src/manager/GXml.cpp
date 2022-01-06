//===============================================
#include "GXml.h"
#include "GLog.h"
//===============================================
GXml::GXml() : GObject() {
    m_node = 0;
    m_doc = 0;
    m_xpath = 0;
    m_xpathObj = 0;
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
        GLOG->addError("Erreur la methode (createXPath) a echoue (1).");
        return *this;
    }
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {
        GLOG->addError("Erreur la methode (createXPath) a echoue (2).");
    }
    return *this;
}
//===============================================
GXml& GXml::queryXPath(const std::string& _query) {
    if(!m_xpath) {
        GLOG->addError("Erreur la methode (queryXPath) a echoue "
                "sur la requete (%s) (1).", _query.c_str());
        return *this;
    }
    m_xpathObj = xmlXPathEvalExpression((xmlChar*)_query.c_str(), m_xpath);
    if(!m_xpathObj) {
        GLOG->addError("Erreur la methode (queryXPath) a echoue "
                "sur la requete (%s) (2).", _query.c_str());
        return *this;
    }
    int lCount = m_xpathObj->nodesetval->nodeNr;
    if(!lCount) {
        GLOG->addError("Erreur la methode (queryXPath) a echoue "
                "sur la requete (%s) (2).", _query.c_str());
        return *this;
    }
    return *this;
}
//===============================================
int GXml::countXPath() const {
    if(!m_xpathObj) {
        return 0;
    }
    int lCount = m_xpathObj->nodesetval->nodeNr;
    return lCount;
}
//===============================================
GXml& GXml::getNodeXPath() {
    if(!m_xpathObj) {
        GLOG->addError("Erreur la methode (getNodeXPath) a echoue (1).");
        m_node = 0;
        return *this;
    }
    int lCount = m_xpathObj->nodesetval->nodeNr;
    if(!lCount) {
        GLOG->addError("Erreur la methode (getNodeXPath) a echoue (1).");
        m_node = 0;
        return *this;
    }
    m_node = m_xpathObj->nodesetval->nodeTab[0];
    return *this;
}
//===============================================
GXml& GXml::getNodeItem(int _index) {
    if(!m_xpathObj) {
        GLOG->addError("Erreur la methode (getNodeItem) a echoue (1).");
        m_node = 0;
        return *this;
    }
    int lCount = m_xpathObj->nodesetval->nodeNr;
    if(_index >= lCount) {
        GLOG->addError("Erreur la methode (getNodeItem) a echoue (2).");
        m_node = 0;
        return *this;
    }
    m_node = m_xpathObj->nodesetval->nodeTab[_index];
    return *this;
}
//===============================================
