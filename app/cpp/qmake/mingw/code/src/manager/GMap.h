//===============================================
#ifndef _GMap_
#define _GMap_
//===============================================
#include "GInclude.h"
//===============================================
class GMap : public std::map<GString, GString> {
public:
    GMap();
    ~GMap();

public:
    GString toParams();
    struct curl_slist* toHeaders(CURL* _curl, struct curl_slist* _headers);

protected:
};
//==============================================
#endif
//==============================================
