//===============================================
#include "GQtXml.h"
#include "GQtLog.h"
//===============================================
GQtXml::GQtXml(QObject* _parent) :
GQtObject(_parent) {
    m_xml = 0;
    m_filename = "";
}
//===============================================
GQtXml::GQtXml(GQtXml* _xml, QObject* _parent) :
GQtObject(_parent) {
    m_xml = _xml;
    m_filename = "";
}
//===============================================
GQtXml::~GQtXml() {

}
//===============================================
bool GQtXml::loadXmlFile(const QString _filename) {
    m_filename = _filename;
    QFile lFile(_filename);
    if (!lFile.open(QFile::ReadOnly | QFile::Text)) {
        GQTLOG->addError(QString("Erreur l'ouverture du fichier a echoué : "
                "Fichier : %1").arg(_filename));
        return false;
    }

    QString lErrorStr;
    int lErrorLine;
    int lErrorColumn;

    if (!m_dom.setContent(&lFile, true, &lErrorStr, &lErrorLine, &lErrorColumn)) {
        GQTLOG->addError(QString("Erreur la création du document à échoué : "
                "Erreur  : %1 "
                "Ligne   : %2 "
                "Colonne.: %3").arg(lErrorStr).arg(lErrorLine).arg(lErrorColumn));
        return false;
    }
    lFile.close();
    return true;
}
//===============================================
bool GQtXml::saveXmlFile(const QString _filename) {
    QString lFilename = "";

    if(_filename != "") {
        lFilename = _filename;
    }
    else if(m_filename != "") {
        lFilename = m_filename;
    }
    else {
        GQTLOG->addError(QString("Erreur la methode (saveFile) a echoue "
                "sur le fichier (%1).").arg(lFilename));
        return false;
    }

    QFile lFile(lFilename);
    if (!lFile.open(QFile::WriteOnly | QFile::Text)) {
        GQTLOG->addError(QString("Erreur la methode (saveFile) a echoue "
                "sur le fichier (%1).").arg(lFilename));
        return false;
    }

    int lIndentSize = 4;
    QTextStream lStreamOut(&lFile);
    m_dom.save(lStreamOut, lIndentSize);

    lFile.close();
    return true;
}
//===============================================
GQtXml& GQtXml::getRoot(const QString& _nodeName) {
    m_node = m_dom.documentElement();
    if(m_node.nodeName() != _nodeName) {
        GQTLOG->addError(QString("Erreur la methode (getRoot) a echoue "
                "sur le noeud (%1).").arg(_nodeName));
        m_node = QDomElement();
    }
    return *this;
}
//===============================================
GQtXml& GQtXml::getNode(const QString& _nodeName) {
    if(!m_node.isNull()) {
        m_node = m_node.firstChildElement(_nodeName);
        if(m_node.isNull()) {
            GQTLOG->addError(QString("Erreur le noeud (%1) n'existe pas").arg(_nodeName));
        }
    }
    else {
        GQTLOG->addError(QString("Erreur la methode (getNode) a echoue "
                "sur le noeud (%1).").arg(_nodeName));
    }
    return *this;
}
//===============================================
GQtXml& GQtXml::getNodeOrEmpty(const QString& _nodeName) {
    if(!m_node.isNull()) {
        m_node = m_node.firstChildElement(_nodeName);
    }
    return *this;
}
//===============================================
int GQtXml::countNode(const QString& _nodeName) const {
    int lCount = 0;
    if(!m_node.isNull()) {
        QDomElement lNode = m_node.firstChildElement(_nodeName);
        while(!lNode.isNull()) {
            lCount++;
            lNode = lNode.nextSiblingElement(_nodeName);
        }
    }
    else {
        GQTLOG->addError(QString("Erreur la methode (getNodeCount) a echoue "
                "sur le noeud (%1).").arg(_nodeName));
    }
    return lCount;
}
//===============================================
GQtXml& GQtXml::clearNode(const QString& _nodeName) {
    if(!m_node.isNull()) {
        QDomElement lNode = m_node.firstChildElement(_nodeName);
        while(!lNode.isNull()) {
            QDomElement lLast = lNode;
            lNode = lNode.nextSiblingElement(_nodeName);
            m_node.removeChild(lLast);
        }
    }
    else {
        GQTLOG->addError(QString("Erreur la methode (clearNode) a echoue "
                "sur le noeud (%1).").arg(_nodeName));
    }
    return *this;
}
//===============================================
bool GQtXml::hasNode(const QString& _nodeName) {
    if(!m_node.isNull()) {
        QDomElement lNode = m_node.firstChildElement(_nodeName);
        if(lNode.isNull()) {
            return false;
        }
    }
    else {
        GQTLOG->addError(QString("Erreur la methode (existeNode) a echoue "
                "sur le noeud (%1).").arg(_nodeName));
        return false;
    }
    return true;
}
//===============================================
GQtXml& GQtXml::appendNode(GQtXml& _node) {
    if(m_node.isNull()) {
        GQTLOG->addError(QString("Erreur la methode (appendNode) a echoue."));
        return *this;
    }
    m_node.appendChild(_node.m_node);
    return *this;
}
//===============================================
GQtXml& GQtXml::setNodeValue(const QString& _value) {
    if(m_node.isNull()) {
        GQTLOG->addError(QString("Erreur la methode (setNodeValue) a echoue."));
        return *this;
    }
    m_node.firstChild().setNodeValue(_value);
    return *this;
}
//===============================================
GQtXml& GQtXml::createNode(const QString& _nodeName) {
    if(!m_xml) {
        GQTLOG->addError(QString("Erreur la methode (createNode) a echoue."));
        return *this;
    }
    m_node = m_xml->m_dom.createElement(_nodeName);
    return *this;
}
//===============================================
GQtXml& GQtXml::createNodeText(const QString& _nodeName, const QString& _text) {
    if(!m_xml) {
        GQTLOG->addError(QString("Erreur la methode (createNodeText) a echoue."));
        return *this;
    }
    m_node = m_xml->m_dom.createElement(_nodeName);
    QDomText lText = m_xml->m_dom.createTextNode(_text);
    m_node.appendChild(lText);
    return *this;
}
//===============================================
GQtXml& GQtXml::createText(const QString& _text) {
    if(!m_xml) {
        GQTLOG->addError(QString("Erreur la methode (createText) a echoue."));
        return *this;
    }
    m_node = m_xml->m_dom.createTextNode(_text).toElement();
    return *this;
}
//===============================================
GQtXml& GQtXml::appendText(const QString& _text) {
    if(!m_xml) {
        GQTLOG->addError(QString("Erreur la methode (appendText) a echoue."));
        return *this;
    }
    QDomText lText = m_xml->m_dom.createTextNode(_text);
    m_node.appendChild(lText);
    return *this;
}
//===============================================
GQtXml& GQtXml::getNodeItem(const QString& _nodeName, int _index) {
    int lCount = 0;
    if(!m_node.isNull()) {
        QDomElement lNode = m_node.firstChildElement(_nodeName);
        while(!lNode.isNull()) {
            if(lCount == _index) {
                m_node = lNode;
                return *this;
            }
            lCount++;
            lNode = lNode.nextSiblingElement(_nodeName);
        }
    }
    else {
        GQTLOG->addError(QString("Erreur la methode (getNodeItem) a echoue "
                "sur le noeud (%1) et l'index (%2).").arg(_nodeName).arg(_index));
    }
    m_node = QDomElement();
    return *this;
}
//===============================================
QString GQtXml::getNodeValue() const {
    QString lValue;
    if(!m_node.isNull()) {
        lValue = m_node.text();
    }
    else {
        GQTLOG->addError(QString("Erreur la methode (getNodeValue) a echoue."));
    }
    return lValue;
}
//===============================================
QString GQtXml::getCData() const {
    QString lValue;
    if(!m_node.isNull()) {
        QDomNode lNode = m_node.firstChild();
        if(!lNode.isCDATASection()) {
            GQTLOG->addError(QString("Erreur la methode (getCData) a echoue (1)."));
            return "";
        }
        QDomCDATASection lCData = lNode.toCDATASection();
        lValue = lCData.data();
    }
    else {
        GQTLOG->addError(QString("Erreur la methode (getCData) a echoue (2)."));
    }
    return lValue;
}
//===============================================
QString GQtXml::getNodeValueOrEmpty() const {
    QString lValue;
    if(!m_node.isNull()) {
        lValue = m_node.text();
    }
    return lValue;
}
//===============================================
