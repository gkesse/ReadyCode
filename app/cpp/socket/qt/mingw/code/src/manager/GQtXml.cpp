//===============================================
#include "GQtXml.h"
#include "GQtLog.h"
//===============================================
GQtXml::GQtXml(QObject* _parent) :
GQtObject(_parent) {

}
//===============================================
GQtXml::~GQtXml() {

}
//===============================================
bool GQtXml::openFileRD(const QString _filename) {
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
QString GQtXml::getNodeValue() {
    QString lValue;
    if(!m_node.isNull()) {
        lValue = m_node.text();
    }
    return lValue;
}
//===============================================
