//===============================================
#include "GMap.h"
//===============================================
GMap::GMap() {

}
//===============================================
GMap::~GMap() {

}
//===============================================
GString GMap::toParams() {
    GString lData;
    std::map<GString, GString>::iterator it = begin();
    for (int i = 0; it != end(); i++, it++) {
        GString lKey = it->first;
        GString lValue = it->second;
        if(i != 0) lData += "&";
        lData += GFORMAT("%s=%s", lKey.c_str(), lValue.c_str());
    }
    return lData;
}
//===============================================
