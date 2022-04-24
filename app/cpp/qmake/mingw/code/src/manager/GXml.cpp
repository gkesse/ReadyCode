//===============================================
#include "GXml.h"
#include "GLog.h"
#include "GError.h"
//===============================================
GXml::GXml(QObject* _parent) : GObject(_parent) {
    m_node = 0;
    m_doc = 0;
    m_xpath = 0;
    m_xpathObj = 0;
    xmlKeepBlanksDefault(0);
    m_errors.reset(new GError(_parent));
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
        GERROR(eGERR, QString(""
                "Erreur lors du chargement du fichier.\n"
                "fichier......: %1\n"
                "").arg(_filename)
        );
    }
    m_filename = _filename;
    return *this;
}
//===============================================
GXml& GXml::loadXmlData(const QString& _data) {
    m_doc = xmlParseDoc(BAD_CAST(_data.toStdString().c_str()));
    if(!m_doc) {
        GERROR(eGERR, QString(""
                "Erreur lors du chargement de la source.\n"
                "source.......: %1\n"
                "").arg(_data)
        );
    }
    return *this;
}
//===============================================
GXml& GXml::loadNodeData(const QString& _data) {
    if(!m_node) return *this;
    xmlNodePtr lNewNode;
    QString lData = "<rdv>" + _data + "</rdv>";
    xmlParseInNodeContext(m_node, lData.toStdString().c_str(), lData.size(), 0, &lNewNode);
    xmlNodePtr lNode = lNewNode->children;
    while(lNode) {
        xmlAddChild(m_node, xmlCopyNode(lNode, 1));
        lNode = lNode->next;
    }
    xmlFreeNode(lNewNode);
    return *this;
}
//===============================================
GXml& GXml::saveXmlFile(const QString& _filename, const QString& _encoding, int _format) {
    QString lFilename = "";

    if(_filename != "") {
        lFilename = _filename;
    }
    else if(m_filename != "") {
        lFilename = m_filename;
    }
    else {
        GERROR(eGERR, QString(""
                "Erreur lors de la sauvegarde du document XML.\n"
                "fichier......: %1\n"
                "").arg(lFilename)
        );
        return *this;
    }

    xmlSaveFormatFileEnc(lFilename.toStdString().c_str(), m_doc, _encoding.toStdString().c_str(), _format);
    return *this;
}
//===============================================
bool GXml::isValidXmlData(const QString& _data) {
    m_doc = xmlParseDoc(BAD_CAST(_data.toStdString().c_str()));
    if(!m_doc) {
        GERROR_OBJ(eGERR, QString(""
                "Erreur le format XML est invalide.\n"
                "source.......: %1\n"
                "").arg(_data)
        );
        return false;
    }
    return true;
}
//===============================================
GXml& GXml::createDoc(const QString& _version) {
    m_doc = xmlNewDoc(BAD_CAST(_version.toStdString().c_str()));
    return *this;
}
//===============================================
GXml& GXml::createDoc(const QString& _version, const QString& _rootNode) {
    createDoc(_version);
    createRoot(_rootNode);
    createXPath();
    return *this;
}
//===============================================
GXml& GXml::createRoot(const QString& _nodename) {
    m_node = xmlNewNode(0, BAD_CAST(_nodename.toStdString().c_str()));
    xmlDocSetRootElement(m_doc, m_node);
    return *this;
}
//===============================================
GXml& GXml::getRoot(const QString& _nodename) {
    m_node = xmlDocGetRootElement(m_doc);
    if(!m_node) {
        GERROR(eGERR, QString(""
                "Erreur la recuperation du noeud.\n"
                "noeud........: %1\n"
                "").arg(_nodename)
        );
        return *this;
    }
    QString lNodeName = (char*)m_node->name;
    if(lNodeName != _nodename) {
        GERROR(eGERR, QString(""
                "Erreur de correspondance dans le nom du neoud.\n"
                "noeud[cur]...: %1\n"
                "noeud[in]....: %2\n"
                "").arg(lNodeName).arg(_nodename)
        );
    }
    return *this;
}
//===============================================
GXml& GXml::getNode(const QString& _nodename) {
    if(!m_node) return *this;
    xmlNodePtr lNode  = xmlFirstElementChild(m_node);
    while(lNode) {
        QString lNodeName = (char*)lNode->name;
        if(lNodeName == _nodename) {
            m_node = lNode;
            return *this;
        }
        lNode = xmlNextElementSibling(lNode);
    }
    GERROR(eGERR, QString(""
            "Erreur lors de la recuperation du noeud.\n"
            "noeud........: %1"
            "").arg(_nodename)
    );
    return *this;
}
//===============================================
QString GXml::getNodeValue() const {
    if(!m_node) return "";
    QString lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
QString GXml::getNodeValue(const QString& _xpath) {
    QString lData = queryXPath(_xpath).getNodeXPath().getNodeValue();
    return lData;
}
//===============================================
GXml& GXml::createNode(const QString& _nodename) {
    m_node = xmlNewNode(NULL, BAD_CAST(_nodename.toStdString().c_str()));
    if(!m_node) {
        GERROR(eGERR, QString(""
                "Erreur lors de la creation du noeud.\n"
                "noeud........: %1\n"
                "").arg(_nodename)
        );
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::createNodeValue(const QString& _nodename, const QString& _value) {
    createNode(_nodename);
    setNodeValue(_value);
    if(!m_node) {
        GERROR(eGERR, QString(""
                "Erreur lors de la creation du noeud.\n"
                "noeud........: %1\n"
                "valeur.......: %2\n"
                "").arg(_nodename).arg(_value)
        );
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::createNodePath(const QString& _path, const QString& _value) {
    if(!m_doc) return *this;
    QStringList lPaths = QString(_path).split('/');
    QString lName = "";
    for(int i = 0; i < lPaths.size(); i++) {
        QString lPath = QString(lPaths.at(i)).trimmed();
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
    if(!_value.isEmpty()) {
        setNodeValue(_value);
    }
    return *this;
}
//===============================================
GXml& GXml::createCData(GXml& _xml, const QString& _value) {
    if(!_xml.m_node) return *this;
    m_node = xmlNewCDataBlock(_xml.m_node->doc, BAD_CAST(_value.toStdString().c_str()), _value.size());
    return *this;
}
//===============================================
GXml& GXml::setNodeValue(const QString& _value) {
    if(!m_node) return *this;
    xmlNodeSetContent(m_node, BAD_CAST(_value.toStdString().c_str()));
    return *this;
}
//===============================================
GXml& GXml::setNodeValue(const QString& _key, const QString& _value) {
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
GXml& GXml::appendNode(const QString& _nodename) {
    if(!m_node) return *this;
    GXml lNode;
    lNode.createNode(_nodename);
    appendNode(lNode);
    return *this;
}
//===============================================
GXml& GXml::appendNode(const QString& _nodename, const QString& _value) {
    if(!m_node) return *this;
    GXml lNode;
    lNode.createNodeValue(_nodename, _value);
    appendNode(lNode);
    return *this;
}
//===============================================
GXml& GXml::appendNodeGet(const QString& _nodename) {
    if(!m_node) return *this;
    GXml lNode;
    lNode.createNode(_nodename);
    appendNode(lNode);
    m_node = lNode.m_node;
    return *this;
}
//===============================================
GXml& GXml::appendNodeGet(const QString& _nodename, const QString& _value) {
    if(!m_node) return *this;
    GXml lNode;
    lNode.createNodeValue(_nodename, _value);
    appendNode(lNode);
    m_node = lNode.m_node;
    return *this;
}
//===============================================
GXml& GXml::appendCData(const QString& _value) {
    if(!m_node) return *this;
    GXml lCData;
    lCData.createCData(*this, _value);
    appendNode(lCData);
    return *this;
}
//===============================================
GXml& GXml::appendCData(const QString& _nodename, const QString& _value) {
    if(!m_node) return *this;
    GXml lNode;
    lNode.createNode(_nodename);
    lNode.appendCData(_value);
    appendNode(lNode);
    return *this;
}
//===============================================
GXml& GXml::replaceNode(GXml& _xml) {
    if(!m_node || !_xml.m_node) return *this;
    xmlReplaceNode(m_node, _xml.m_node);
    xmlFreeNode(m_node);
    return *this;
}
//===============================================
GXml& GXml::createXPath() {
    if(!m_doc) return *this;
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {
        GERROR(eGERR, QString("Erreur lors de la creation de l'objet XPath.\n"));
        return *this;
    }
    return *this;
}
//===============================================
GXml& GXml::queryXPath(const QString& _query) {
    if(!m_xpath) return *this;
    m_xpathObj = xmlXPathEvalExpression((xmlChar*)_query.toStdString().c_str(), m_xpath);
    if(!m_xpathObj) {
        GERROR(eGERR, QString("Erreur lors de l'execution de la requete XPath.\n"));
        return *this;
    }
    return *this;
}
//===============================================
int GXml::countXPath() const {
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
GXml& GXml::createNodeCData(GXml& _xml, const QString& _value) {
    if(!_xml.m_node) return *this;
    m_node = xmlNewCDataBlock(_xml.m_node->doc, BAD_CAST(_value.toStdString().c_str()), _value.size());
    if(!m_node) {
        GERROR(eGERR, QString(""
                "Erreur lors de la creation du noeud CData.\n"
                "noeud........: %1\n"
                "").arg(_value)
        );
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
    if(!m_node) return *this;
    GXml lNode;
    lNode.createNodeCData((char*)m_node->name, _value);
    replaceNode(lNode);
    return *this;
}
//===============================================
QString GXml::getNodeCData() const {
    if(!m_node) return "";
    QString lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
QString GXml::toString(const QString& _encoding, int _format) const {
    if(!m_doc) return "";
    xmlChar* lBuffer = NULL;
    int lSize;
    xmlDocDumpFormatMemoryEnc(m_doc, &lBuffer, &lSize, _encoding.toStdString().c_str(), _format);
    QString lData = (char*)lBuffer;
    xmlFree(lBuffer);
    return lData;
}
//===============================================
QString GXml::toStringNode(const QString& _encoding, int _format) const {
    if(!m_node) return "";
    xmlBufferPtr lBuffer = xmlBufferCreate();
    xmlNodeDump(lBuffer, m_doc, m_node, 0, 1);
    QString lData = (char*)lBuffer->content;
    xmlBufferFree(lBuffer);
    return lData;
}
//===============================================
