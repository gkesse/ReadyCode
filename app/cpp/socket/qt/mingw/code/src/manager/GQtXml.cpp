//===============================================
#include "GQtXml.h"
#include "GQtLog.h"
//===============================================
GQtXml::GQtXml(QObject* _parent) :
GQtObject(_parent) {
    m_filename = "";
}
//===============================================
GQtXml::~GQtXml() {

}
//===============================================
bool GQtXml::openFileRD(const QString _filename) {
    m_filename = _filename;
    QFile lFile(_filename);
    if (!lFile.open(QFile::ReadOnly | QFile::Text)) {
        GQTLOG->addError(QString("Erreur l'ouverture du fichier a echoué :\n"
                "Fichier : %1").arg(_filename));
        return false;
    }

    QString lErrorStr;
    int lErrorLine;
    int lErrorColumn;

    if (!m_dom.setContent(&lFile, true, &lErrorStr, &lErrorLine, &lErrorColumn)) {
        GQTLOG->addError(QString("Erreur la création du document à échoué :\n"
                "Erreur  : %1\n"
                "Ligne   : %2\n"
                "Colonne.: %3").arg(lErrorStr).arg(lErrorLine).arg(lErrorColumn));
        return false;
    }
    lFile.close();
    return true;
}
//===============================================
bool GQtXml::saveFile(const QString _filename) {
    QString lFilename = "";

    if(_filename != "") {
        lFilename = _filename;
    }
    else if(m_filename != "") {
        lFilename = m_filename;
    }
    else {
        GQTLOG->addError(QString("Erreur le nom du fichier est vide."));
        return false;
    }

    QFile lFile(lFilename);
    if (!lFile.open(QFile::WriteOnly | QFile::Text)) {
        GQTLOG->addError(QString("Erreur l'ouverture du fichier a echoué :\n"
                "Fichier : %1").arg(_filename));
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
        GQTLOG->addError(QString("Erreur le noeud racine (%1) n'existe pas").arg(_nodeName));
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
        GQTLOG->addError(QString("Erreur le noeud courant est nul"));
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
int GQtXml::getNodeCount(const QString& _nodeName) const {
    int lCount = 0;
    if(!m_node.isNull()) {
        QDomElement lNode = m_node.firstChildElement(_nodeName);
        while(!lNode.isNull()) {
            lCount++;
            lNode = lNode.nextSiblingElement(_nodeName);
        }
    }
    else {
        GQTLOG->addError(QString("Erreur le noeud courant est nul"));
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
        GQTLOG->addError(QString("Erreur la suppression du noeud a échoué."));
    }
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
        GQTLOG->addError(QString("Erreur le noeud courant est nul"));
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
        GQTLOG->addError(QString("Erreur le noeud courant est nul"));
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
