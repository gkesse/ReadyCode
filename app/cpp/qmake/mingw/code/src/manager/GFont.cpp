//===============================================
#include "GFont.h"
#include "GPath.h"
#include "GLog.h"
//===============================================
GFont::GFont(QObject* _parent) :
GObject(_parent) {
    createDoms();
}
//===============================================
GFont::~GFont() {

}
//===============================================
void GFont::loadFont() {
    int lCount = countItem("fonts");
    for(int i = 0; i < lCount; i++) {
        QString lFont = getItem("fonts", i);
        QString lFile = GRES("fonts", lFont);
        QFontDatabase::addApplicationFont(lFile);
    }
}
//===============================================
