//===============================================
#include "GStyle2.h"
#include "GPath2.h"
#include "GFile2.h"
#include "GLog2.h"
//===============================================
GStyle2* GStyle2::m_instance = 0;
//===============================================
GStyle2::GStyle2()
: GObject2() {

}
//===============================================
GStyle2::~GStyle2() {

}
//===============================================
GStyle2* GStyle2::Instance() {
    if(m_instance == 0) {
        m_instance = new GStyle2;
    }
    return m_instance;
}
//===============================================
bool GStyle2::loadStyle() {
    GString lFile = GPATH("css", "style.css");
    if(!loadStyle(lFile)) return false;
    return true;
}
//===============================================
bool GStyle2::loadStyle(const GString& _filename) {
    GFile2 lFiles(_filename);
    if(!lFiles.existFile()) {GERROR_ADD2(eGERR, GFORMAT("La feuille de style n'existe pas.\n%s", _filename.c_str())); return false;}
    GString lStyleSheet = lFiles.getContent();
    qApp->setStyleSheet(lStyleSheet.c_str());
    return true;
}
//===============================================
