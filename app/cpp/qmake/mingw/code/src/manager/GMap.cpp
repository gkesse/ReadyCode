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
struct curl_slist* GMap::toHeaders(CURL* _curl, struct curl_slist* _headers) {
    std::map<GString, GString>::iterator it = begin();
    for (int i = 0; it != end(); i++, it++) {
        GString lKey = it->first;
        GString lValue = it->second;
        GString lData = GFORMAT("%s: %s", lKey.c_str(), lValue.c_str());
        _headers = curl_slist_append(_headers, lData.c_str());
    }
    return _headers;
}
//===============================================
