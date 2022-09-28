//===============================================
#include "GStyle.h"
#include "GPath.h"
#include "GLog.h"
//===============================================
GStyle* GStyle::m_instance = 0;
//===============================================
GStyle::GStyle()
: GObject() {

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
bool GStyle::loadStyle() {
    GPath lPath;
    QString lFile = lPath.getPath("css", "style.css");
    if(!loadStyle(lFile)) return false;
    return true;
}
//===============================================
bool GStyle::loadStyle(const QString& _filename) {
    QFile lFile(_filename);
    if(!lFile.open(QFile::ReadOnly)) {
        GERROR_ADD(eGERR, QString(""
                "Erreur lors du chargement du style.\n"
                "fichier : (%1)\n"
                "").arg(_filename));
        return false;
    }
    QString lStyleSheet = QLatin1String(lFile.readAll());
    qApp->setStyleSheet(lStyleSheet);
    return true;
}
//===============================================
