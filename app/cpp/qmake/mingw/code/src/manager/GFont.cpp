//===============================================
#include "GFont.h"
#include "GPath.h"
#include "GCode.h"
//===============================================
GFont* GFont::m_instance = 0;
//===============================================
GFont::GFont() :
GObject() {
    createDoms();
}
//===============================================
GFont::~GFont() {

}
//===============================================
GFont* GFont::Instance() {
    if(m_instance == 0) {
        m_instance = new GFont;
    }
    return m_instance;
}
//===============================================
bool GFont::loadFont() {
    int lCount = m_dom->countMap("fonts");
    for(int i = 0; i < lCount; i++) {
        GString lFont = GAPP->getData("fonts", i);
        GString lFile = GPATH("fonts", lFont);
        QFontDatabase::addApplicationFont(lFile.c_str());
    }
    return true;
}
//===============================================
