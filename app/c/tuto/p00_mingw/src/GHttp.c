//===============================================
#include "GHttp.h"
//===============================================
static void GHttp_delete(GHttp** _this);
static void GHttp_toResponse(GHttp* _this, GString* _data, const char* _msg);
//===============================================
GHttp* GHttp_new() {
    GHttp* lObj = (GHttp*)malloc(sizeof(GHttp));
    GHttp_init(lObj);
    return lObj;
}
//===============================================
void GHttp_init(GHttp* _this) {
    assert(_this);
    _this->delete = GHttp_delete;
    _this->toResponse = GHttp_toResponse;
}
//===============================================
static void GHttp_delete(GHttp** _this) {
    assert(*_this);
    free(*_this);
    (*_this) = 0;
}
//===============================================
static void GHttp_toResponse(GHttp* _this, GString* _data, const char* _msg) {
    assert(_this);
    int lSize = strlen(_msg);
    _data->format(_data, ""
            "HTTP/1.1 200 OK\r\n"
            "Content-Length: %d\r\n"
            "\r\n"
            "%s"
            "", lSize, _msg);
}
//===============================================
