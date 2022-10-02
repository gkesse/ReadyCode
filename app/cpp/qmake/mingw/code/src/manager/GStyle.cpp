//===============================================
#include "GStyle.h"
#include "GPath.h"
#include "GLog.h"
#include "GFile.h"
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
    GString lFile = GPATH("css", "style.css");
    if(!loadStyle(lFile)) return false;
    return true;
}
//===============================================
bool GStyle::loadStyle(const GString& _filename) {
    GFile2 lFiles(_filename);
    if(!lFiles.existFile()) {GERROR_ADD(eGERR, GFORMAT("La feuille de style n'existe pas.\n%s", _filename.c_str())); return false;}
    GString lStyleSheet = lFiles.getContent();
    qApp->setStyleSheet(lStyleSheet.c_str());
    return true;
}
//===============================================
