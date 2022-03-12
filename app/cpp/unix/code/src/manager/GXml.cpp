//===============================================
#include "GXml.h"
#include "GLog.h"
#include "GFormat.h"
#include "GString.h"
//===============================================
GXml::GXml() : GObject() {
    m_node = 0;
    m_doc = 0;
    m_xpath = 0;
    m_xpathObj = 0;
    //
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
    if(GLOGI->hasError()) return;
    xmlInitParser();
}
//===============================================
void GXml::cleanModule() {
    if(GLOGI->hasError()) return;
    xmlCleanupParser();
    xmlMemoryDump();
}
//===============================================
GXml& GXml::loadXmlFile(const std::string& _filename) {
    if(GLOGI->hasError()) return *this;
    m_doc = xmlParseFile(_filename.c_str());
    if(!m_doc) {
        GLOG("Erreur la methode (GXml::loadXmlFile) a echoue (1)\n"
                "- fichier.....: (%s).", _filename.c_str());
    }
    m_filename = _filename;
    return *this;
}
//===============================================
bool GXml::saveXmlFile(const std::string& _filename, const std::string& _encoding, int _format) {
    if(GLOGI->hasError()) return false;
    std::string lFilename = "";

    if(_filename != "") {
        lFilename = _filename;
    }
    else if(m_filename != "") {
        lFilename = m_filename;
    }
    else {
        GLOG("Erreur la methode (saveXmlFile) a echoue (1)\n"
                "- fichier.....: (%s).", lFilename.c_str());
        return false;
    }

    xmlSaveFormatFileEnc(lFilename.c_str(), m_doc, _encoding.c_str(), _format);
    return true;
}
//===============================================
GXml& GXml::createDoc(const std::string& _version) {
    if(GLOGI->hasError()) return *this;
    m_doc = xmlNewDoc(BAD_CAST(_version.c_str()));
    return *this;
}
//===============================================
GXml& GXml::createRoot(const std::string& _nodename) {
    if(GLOGI->hasError()) return *this;
    m_node = xmlNewNode(0, BAD_CAST(_nodename.c_str()));
    xmlDocSetRootElement(m_doc, m_node);
    return *this;
}
//===============================================
GXml& GXml::getRoot(const std::string& _nodename) {
    if(GLOGI->hasError()) return *this;
    m_node = xmlDocGetRootElement(m_doc);
    if(!m_node) {
        GLOG("Erreur la methode (GXml::getRoot) a echoue (1)\n"
                "- noeud.....: (%s).", _nodename.c_str());
        return *this;
    }
    std::string lNodeName = (char*)m_node->name;
    if(lNodeName != _nodename) {
        GLOG("Erreur la methode (GXml::getRoot) a echoue (2)\n"
                "- noeud.....: (%s).", _nodename.c_str());
    }
    return *this;
}
//===============================================
GXml& GXml::getNode(const std::string& _nodename) {
    if(GLOGI->hasError()) return *this;
    if(!m_node) {
        GLOG("Erreur la methode (GXml::getNode) a echoue (1)\n"
                "- noeud.....: (%s).", _nodename.c_str());
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
    GLOG("Erreur la methode (GXml::getNode) a echoue (2)\n"
            "- noeud.....: (%s).", _nodename.c_str());
    return *this;
}
//===============================================
std::string GXml::getNodeValue() const {
    if(GLOGI->hasError()) return "";
    if(!m_node) {
        return "";
    }
    std::string lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
GXml& GXml::createNode(const std::string& _nodename) {
    if(GLOGI->hasError()) return *this;
    m_node = xmlNewNode(NULL, BAD_CAST(_nodename.c_str()));
    if(!m_node) {
        GLOG("Erreur la methode (GXml::createNode) a echoue (1)\n"
                "- noeud.....: (%s).", _nodename.c_str());
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::createNodePath(const std::string& _path) {
    if(GLOGI->hasError()) return *this;
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
    if(GLOGI->hasError()) return *this;
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
GXml& GXml::createNodeValue(const std::string& _nodename, const std::string& _value) {
    if(GLOGI->hasError()) return *this;
    createNode(_nodename);
    setNodeValue(_value);
    if(!m_node) {
        GLOG("Erreur la methode (GXml::createNodeValue) a echoue (1)\n"
                "- noeud.....: (%s).\n"
                "- valeur....: (%s).", _nodename.c_str(), _value.c_str());
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::setNodeValue(const std::string& _value) {
    if(GLOGI->hasError()) return *this;
    if(!m_node) {
        GLOG("Erreur la methode (GXml::setNodeValue) a echoue (1)\n"
                "- valeur....: (%s).", _value.c_str());
        return *this;
    }
    xmlNodeSetContent(m_node, BAD_CAST(_value.c_str()));
    return *this;
}
//===============================================
GXml& GXml::appendNode(GXml& _xml) {
    if(GLOGI->hasError()) return *this;
    if(!m_node) {
        GLOG("Erreur la methode (GXml::appendNode) a echoue (1)\n");
        return *this;
    }
    xmlAddChild(m_node, _xml.m_node);
    return *this;
}
//===============================================
GXml& GXml::replaceNode(GXml& _xml) {
    if(GLOGI->hasError()) return *this;
    if(!m_node || !_xml.m_node) {
        GLOG("Erreur la methode (GXml::replaceNode) a echoue (1)\n");
        return *this;
    }
    xmlReplaceNode(m_node, _xml.m_node);
    xmlFreeNode(m_node);
    return *this;
}
//===============================================
GXml& GXml::createXPath() {
    if(GLOGI->hasError()) return *this;
    if(!m_doc) {
        GLOG("Erreur la methode (GXml::createXPath) a echoue (1)\n");
        return *this;
    }
    m_xpath = xmlXPathNewContext(m_doc);
    return *this;
}
//===============================================
GXml& GXml::queryXPath(const std::string& _query) {
    if(GLOGI->hasError()) return *this;
    if(!m_xpath) {
        return *this;
    }
    m_xpathObj = xmlXPathEvalExpression((xmlChar*)_query.c_str(), m_xpath);
    return *this;
}
//===============================================
int GXml::countXPath() const {
    if(GLOGI->hasError()) return 0;
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
    if(GLOGI->hasError()) return *this;
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
    if(GLOGI->hasError()) return *this;
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
    if(GLOGI->hasError()) return *this;
    for(int i = 0; i < countXPath(); i++) {
        xmlNodePtr lNode = m_xpathObj->nodesetval->nodeTab[i];
        xmlUnlinkNode(lNode);
        xmlFreeNode(lNode);
    }
    return *this;
}
//===============================================
GXml& GXml::createNodeCData(GXml& _xml, const std::string& _value) {
    if(GLOGI->hasError()) return *this;
    if(!_xml.m_node) {
        GLOG("Erreur la methode (GXml::createNodeCData) a echoue (1)\n"
                "- valeur.....: (%s).", _value.c_str());
        return *this;
    }
    m_node = xmlNewCDataBlock(_xml.m_node->doc, BAD_CAST(_value.c_str()), _value.size());
    if(!m_node) {
        GLOG("Erreur la methode (GXml::createNodeCData) a echoue (2)\n"
                "- valeur.....: (%s).", _value.c_str());
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::createNodeCData(const std::string& _nodename, const std::string& _value) {
    if(GLOGI->hasError()) return *this;
    createNode(_nodename);
    GXml lNode;
    lNode.createNodeCData(*this, _value);
    appendNode(lNode);
    return *this;
}
//===============================================
GXml& GXml::setNodeCData(const std::string& _value) {
    if(GLOGI->hasError()) return *this;
    if(!m_node) {
        GLOG("Erreur la methode (GXml::setNodeCData) a echoue (2)\n"
                "- valeur.....: (%s).", _value.c_str());
        return *this;
    }
    GXml lNode;
    lNode.createNodeCData((char*)m_node->name, _value);
    replaceNode(lNode);
    return *this;
}
//===============================================
std::string GXml::getNodeCData() const {
    if(GLOGI->hasError()) return "";
    if(!m_node) {
        return "";
    }
    std::string lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
std::string GXml::toString(const std::string& _encoding, int _format) const {
    if(GLOGI->hasError()) return "";
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
