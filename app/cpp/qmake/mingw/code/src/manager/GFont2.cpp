//===============================================
#include "GFont2.h"
#include "GPath2.h"
#include "GCode2.h"
//===============================================
GFont2* GFont2::m_instance = 0;
//===============================================
GFont2::GFont2() :
GObject2() {
    createDoms();
}
//===============================================
GFont2::~GFont2() {

}
//===============================================
GFont2* GFont2::Instance() {
    if(m_instance == 0) {
        m_instance = new GFont2;
    }
    return m_instance;
}
//===============================================
bool GFont2::loadFont() {
    int lCount = m_dom->countMap("fonts");
    for(int i = 0; i < lCount; i++) {
        GString lFont = m_dom->getData("fonts", i);
        GString lFile = GPATH("fonts", lFont);
        QFontDatabase::addApplicationFont(lFile.c_str());
    }
    return true;
}
//===============================================
