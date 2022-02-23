//===============================================
#include "GXml.h"
#include "GLog.h"
//===============================================
GXml::GXml(QObject* _parent) :
GObject(_parent) {
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
GXml& GXml::loadXmlFile(const QString& _filename) {
    m_doc = xmlParseFile(_filename.toStdString().c_str());
    if(!m_doc) {
        GLOG->addError(QString("Erreur la methode (loadXmlFile) a echoue "
                "sur le fichier (%1).").arg(_filename));
    }
    m_filename = _filename;
    return *this;
}
//===============================================
bool GXml::saveXmlFile(const QString& _filename, const QString& _encoding, int _format) {
    QString lFilename = "";

    if(_filename != "") {
        lFilename = _filename;
    }
    else if(m_filename != "") {
        lFilename = m_filename;
    }
    else {
        GLOG->addError(QString("Erreur la methode (saveXmlFile) a echoue "
                "sur le fichier (%1).").arg(lFilename));
        return false;
    }

    xmlSaveFormatFileEnc(lFilename.toStdString().c_str(), m_doc, _encoding.toStdString().c_str(), _format);
    return true;
}
//===============================================
GXml& GXml::getRoot(const QString& _nodename) {
    m_node = xmlDocGetRootElement(m_doc);
    if(!m_node) {
        GLOG->addError(QString("Erreur la methode (getRoot) a echoue "
                "sur le noeud (%1) (1).").arg(_nodename));
        return *this;
    }
    QString lNodeName = (char*)m_node->name;
    if(lNodeName != _nodename) {
        GLOG->addError(QString("Erreur la methode (getRoot) a echoue "
                "sur le noeud (%1) (2).").arg(_nodename));
    }
    return *this;
}
//===============================================
GXml& GXml::getNode(const QString& _nodename) {
    if(!m_node) {
        GLOG->addError(QString("Erreur la methode (getNode) a echoue "
                "sur le noeud (%s) (1).").arg(_nodename));
        return *this;
    }
    xmlNodePtr lNode  = xmlFirstElementChild(m_node);
    while(lNode) {
        QString lNodeName = (char*)lNode->name;
        if(lNodeName == _nodename) {
            m_node = lNode;
            return *this;
        }
        lNode = xmlNextElementSibling(lNode);
    }
    GLOG->addError(QString("Erreur la methode (getNode) a echoue "
            "sur le noeud (%1) (2).").arg(_nodename));
    return *this;
}
//===============================================
QString GXml::getNodeValue() const {
    if(!m_node) {
        return "";
    }
    QString lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
GXml& GXml::createNode(const QString& _nodename) {
    m_node = xmlNewNode(NULL, BAD_CAST(_nodename.toStdString().c_str()));
    if(!m_node) {
        GLOG->addError(QString("Erreur la methode (createNode) a echoue "
                "sur le noeud (%1).").arg(_nodename));
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::createNodeValue(const QString& _nodename, const QString& _value) {
    createNode(_nodename);
    setNodeValue(_value);
    if(!m_node) {
        GLOG->addError(QString("Erreur la methode (createNodeValue) a echoue "
                "sur le noeud (%1) avec la valeur (%2).").arg(_nodename).arg(_value));
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::setNodeValue(const QString& _value) {
    if(!m_node) {
        GLOG->addError(QString("Erreur la methode (setNodeValue) a echoue "
                "sur le noeud (%1).").arg(_value));
        return *this;
    }
    xmlNodeSetContent(m_node, BAD_CAST(_value.toStdString().c_str()));
    return *this;
}
//===============================================
GXml& GXml::appendNode(GXml& _xml) {
    if(!m_node) {
        GLOG->addError(QString("Erreur la methode (appendNode) a echoue "
                "sur le noeud (%1)."));
        return *this;
    }
    xmlAddChild(m_node, _xml.m_node);
    return *this;
}
//===============================================
GXml& GXml::replaceNode(GXml& _xml) {
    if(!m_node || !_xml.m_node) {
        GLOG->addError(QString("Erreur la methode (replaceNode) a echoue."));
        return *this;
    }
    xmlReplaceNode(m_node, _xml.m_node);
    xmlFreeNode(m_node);
    return *this;
}
//===============================================
GXml& GXml::createXPath() {
    if(!m_doc) {
        GLOG->addError(QString("Erreur la methode (createXPath) a echoue (1)."));
        return *this;
    }
    m_xpath = xmlXPathNewContext(m_doc);
    return *this;
}
//===============================================
GXml& GXml::queryXPath(const QString& _query) {
    if(!m_xpath) {
        return *this;
    }
    m_xpathObj = xmlXPathEvalExpression((xmlChar*)_query.toStdString().c_str(), m_xpath);
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
GXml& GXml::createNodeCData(GXml& _xml, const QString& _value) {
    if(!_xml.m_node) {
        GLOG->addError(QString("Erreur la methode (createNodeCData) a echoue "
                "sur le noeud (%1) (1).").arg(_value));
        return *this;
    }
    m_node = xmlNewCDataBlock(_xml.m_node->doc, BAD_CAST(_value.toStdString().c_str()), _value.size());
    if(!m_node) {
        GLOG->addError(QString("Erreur la methode (createNodeCData) a echoue "
                "sur le noeud (%1) (2).").arg(_value));
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::createNodeCData(const QString& _nodename, const QString& _value) {
    createNode(_nodename);
    GXml lNode;
    lNode.createNodeCData(*this, _value);
    appendNode(lNode);
    return *this;
}
//===============================================
GXml& GXml::setNodeCData(const QString& _value) {
    if(!m_node) {
        GLOG->addError(QString("Erreur la methode (setNodeCData) a echoue "
                "sur le noeud (%1).").arg(_value));
        return *this;
    }
    GXml lNode;
    lNode.createNodeCData((char*)m_node->name, _value);
    replaceNode(lNode);
    return *this;
}
//===============================================
QString GXml::getNodeCData() const {
    if(!m_node) {
        return "";
    }
    QString lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
