//===============================================
#include "GQtXml.h"
#include "GQtLog.h"
//===============================================
GQtXml::GQtXml(QObject* _parent) :
GQtObject(_parent) {
    m_node = 0;
    m_doc = 0;
    m_xpath = 0;
    m_xpathObj = 0;

    xmlKeepBlanksDefault(0);
}
//===============================================
GQtXml::~GQtXml() {
    xmlXPathFreeObject(m_xpathObj);
    xmlXPathFreeContext(m_xpath);
    xmlFreeDoc(m_doc);
    xmlCleanupParser();
    xmlMemoryDump();
}
//===============================================
GQtXml& GQtXml::loadXmlFile(const QString& _filename) {
    m_doc = xmlParseFile(_filename.toStdString().c_str());
    if(!m_doc) {
        GQTLOG->addError(QString("Erreur la methode (loadXmlFile) a echoue "
                "sur le fichier (%1).").arg(_filename));
    }
    m_filename = _filename;
    return *this;
}
//===============================================
bool GQtXml::saveXmlFile(const QString& _filename, const QString& _encoding, int _format) {
    QString lFilename = "";

    if(_filename != "") {
        lFilename = _filename;
    }
    else if(m_filename != "") {
        lFilename = m_filename;
    }
    else {
        GQTLOG->addError(QString("Erreur la methode (saveXmlFile) a echoue "
                "sur le fichier (%1).").arg(lFilename));
        return false;
    }

    xmlSaveFormatFileEnc(lFilename.toStdString().c_str(), m_doc, _encoding.toStdString().c_str(), _format);
    return true;
}
//===============================================
GQtXml& GQtXml::getRoot(const QString& _nodename) {
    m_node = xmlDocGetRootElement(m_doc);
    if(!m_node) {
        GQTLOG->addError(QString("Erreur la methode (getRoot) a echoue "
                "sur le noeud (%1) (1).").arg(_nodename));
        return *this;
    }
    QString lNodeName = (char*)m_node->name;
    if(lNodeName != _nodename) {
        GQTLOG->addError(QString("Erreur la methode (getRoot) a echoue "
                "sur le noeud (%1) (2).").arg(_nodename));
    }
    return *this;
}
//===============================================
GQtXml& GQtXml::getNode(const QString& _nodename) {
    if(!m_node) {
        GQTLOG->addError(QString("Erreur la methode (getNode) a echoue "
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
    GQTLOG->addError(QString("Erreur la methode (getNode) a echoue "
            "sur le noeud (%1) (2).").arg(_nodename));
    return *this;
}
//===============================================
QString GQtXml::getNodeValue() const {
    if(!m_node) {
        return "";
    }
    QString lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
GQtXml& GQtXml::createNode(const QString& _nodename) {
    m_node = xmlNewNode(NULL, BAD_CAST(_nodename.toStdString().c_str()));
    if(!m_node) {
        GQTLOG->addError(QString("Erreur la methode (createNode) a echoue "
                "sur le noeud (%1).").arg(_nodename));
        return *this;
    }
    return *this;
}
//===============================================
GQtXml& GQtXml::createNodeValue(const QString& _nodename, const QString& _value) {
    createNode(_nodename);
    setNodeValue(_value);
    if(!m_node) {
        GQTLOG->addError(QString("Erreur la methode (createNodeValue) a echoue "
                "sur le noeud (%1) avec la valeur (%2).").arg(_nodename).arg(_value));
        return *this;
    }
    return *this;
}
//===============================================
GQtXml& GQtXml::setNodeValue(const QString& _value) {
    if(!m_node) {
        GQTLOG->addError(QString("Erreur la methode (setNodeValue) a echoue "
                "sur le noeud (%1).").arg(_value));
        return *this;
    }
    xmlNodeSetContent(m_node, BAD_CAST(_value.toStdString().c_str()));
    return *this;
}
//===============================================
GQtXml& GQtXml::appendNode(GQtXml& _xml) {
    if(!m_node) {
        GQTLOG->addError(QString("Erreur la methode (appendNode) a echoue "
                "sur le noeud (%1)."));
        return *this;
    }
    xmlAddChild(m_node, _xml.m_node);
    return *this;
}
//===============================================
GQtXml& GQtXml::replaceNode(GQtXml& _xml) {
    if(!m_node || !_xml.m_node) {
        GQTLOG->addError(QString("Erreur la methode (replaceNode) a echoue."));
        return *this;
    }
    xmlReplaceNode(m_node, _xml.m_node);
    xmlFreeNode(m_node);
    return *this;
}
//===============================================
GQtXml& GQtXml::createXPath() {
    if(!m_doc) {
        GQTLOG->addError(QString("Erreur la methode (createXPath) a echoue (1)."));
        return *this;
    }
    m_xpath = xmlXPathNewContext(m_doc);
    return *this;
}
//===============================================
GQtXml& GQtXml::queryXPath(const QString& _query) {
    if(!m_xpath) {
        return *this;
    }
    m_xpathObj = xmlXPathEvalExpression((xmlChar*)_query.toStdString().c_str(), m_xpath);
    return *this;
}
//===============================================
int GQtXml::countXPath() const {
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
GQtXml& GQtXml::getNodeXPath() {
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
GQtXml& GQtXml::getNodeItem(int _index) {
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
GQtXml& GQtXml::clearNodeXPath() {
    for(int i = 0; i < countXPath(); i++) {
        xmlNodePtr lNode = m_xpathObj->nodesetval->nodeTab[i];
        xmlUnlinkNode(lNode);
        xmlFreeNode(lNode);
    }
    return *this;
}
//===============================================
GQtXml& GQtXml::createNodeCData(GQtXml& _xml, const QString& _value) {
    if(!_xml.m_node) {
        GQTLOG->addError(QString("Erreur la methode (createNodeCData) a echoue "
                "sur le noeud (%1) (1).").arg(_value));
        return *this;
    }
    m_node = xmlNewCDataBlock(_xml.m_node->doc, BAD_CAST(_value.toStdString().c_str()), _value.size());
    if(!m_node) {
        GQTLOG->addError(QString("Erreur la methode (createNodeCData) a echoue "
                "sur le noeud (%1) (2).").arg(_value));
        return *this;
    }
    return *this;
}
//===============================================
GQtXml& GQtXml::createNodeCData(const QString& _nodename, const QString& _value) {
    createNode(_nodename);
    GQtXml lNode;
    lNode.createNodeCData(*this, _value);
    appendNode(lNode);
    return *this;
}
//===============================================
GQtXml& GQtXml::setNodeCData(const QString& _value) {
    if(!m_node) {
        GQTLOG->addError(QString("Erreur la methode (setNodeCData) a echoue "
                "sur le noeud (%1).").arg(_value));
        return *this;
    }
    GQtXml lNode;
    lNode.createNodeCData((char*)m_node->name, _value);
    replaceNode(lNode);
    return *this;
}
//===============================================
QString GQtXml::getNodeCData() const {
    if(!m_node) {
        return "";
    }
    QString lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
