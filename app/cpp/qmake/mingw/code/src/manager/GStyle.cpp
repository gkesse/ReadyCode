//===============================================
#include "GStyle.h"
#include "GLog.h"
//===============================================
GStyle* GStyle::m_instance = 0;
//===============================================
GStyle::GStyle(QObject* _parent) :
GObject(_parent) {

}
//===============================================
GStyle::~GStyle() {

}
//===============================================
GStyle* GStyle::Instance() {
    if(m_instance == 0) {
        m_instance = new GStyle;
    }
    return m_instance;
}
//===============================================
void GStyle::loadStyle(const QString& _filename) {
    QFile lFile(_filename);
    if(!lFile.open(QFile::ReadOnly)) {
        GERROR(eGERR, QString("Erreur la methode (loadStyle) a echoue "
                "sur le fichier (%1).").arg(_filename));
        return;
    }
    QString lStyleSheet = QLatin1String(lFile.readAll());
    qApp->setStyleSheet(lStyleSheet);
}
//===============================================
