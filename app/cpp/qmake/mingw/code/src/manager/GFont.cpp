//===============================================
#include "GFont.h"
#include "GPath.h"
#include "GLog.h"
//===============================================
GFont::GFont() :
GObject() {
    createDoms();
}
//===============================================
GFont::~GFont() {

}
//===============================================
bool GFont::loadFont() {
    if(GLOGI->hasErrors()) return false;
    GPath lPath;
    int lCount = countItem("fonts");
    for(int i = 0; i < lCount; i++) {
        QString lFont = getItem("fonts", i);
        QString lFile = lPath.getPath("fonts", lFont);
        QFontDatabase::addApplicationFont(lFile);
    }
    return true;
}
//===============================================
