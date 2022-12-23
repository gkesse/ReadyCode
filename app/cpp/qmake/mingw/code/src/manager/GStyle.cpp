//===============================================
#include "GStyle.h"
#include "GPath.h"
#include "GFile.h"
//===============================================
GStyle* GStyle::m_instance = 0;
//===============================================
GStyle::GStyle()
: GObject() {
    initStyle();
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
void GStyle::initStyle() {
    m_styleFile = GPATH("css", "style.css");
}
//===============================================
bool GStyle::loadStyle() {
    GFile lFile(m_styleFile);
    if(!lFile.existFile()) {GERROR_ADD(eGERR, "La feuille de style n'existe pas.\n%s", m_styleFile.c_str()); return false;}
    GString lStyleSheet = lFile.getContents();
    qApp->setStyleSheet(lStyleSheet.c_str());
    return true;
}
//===============================================
