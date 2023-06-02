//===============================================
#include "GString.h"
#include "GVector.h"
#include "GJson.h"
#include "GCode.h"
//===============================================
static void GString_delete(GString* _this);
static void GString_clear(GString* _this);
static void GString_allocate(GString* _this, int _size);
static GString* GString_create(GString* _this, const char* _data);
static GString* GString_assign(GString* _this, GString* _data);
static void GString_add(GString* _this, const char* _data);
static const char* GString_format(GString* _this, const char* _format, ...);
static GVector* GString_split(GString* _this, const char* _data, const char* _sep);
static int GString_isEmpty(GString* _this);
static GString* GString_toBase64(GString* _this);
static GString* GString_toJson(GString* _this);
static GString* GString_fromBase64(GString* _this);
static void GString_print(GString* _this);
//===============================================
GString* GString_new() {
    GString* lObj = (GString*)malloc(sizeof(GString));
    lObj->m_data = 0;
    lObj->m_size = 0;

    lObj->delete = GString_delete;
    lObj->clear = GString_clear;
    lObj->allocate = GString_allocate;
    lObj->create = GString_create;
    lObj->assign = GString_assign;
    lObj->add = GString_add;
    lObj->format = GString_format;
    lObj->split = GString_split;
    lObj->isEmpty = GString_isEmpty;
    lObj->toBase64 = GString_toBase64;
    lObj->toJson = GString_toJson;
    lObj->fromBase64 = GString_fromBase64;
    lObj->print = GString_print;
    return lObj;
}
//===============================================
static void GString_delete(GString* _this) {
    assert(_this);
    _this->clear(_this);
    free(_this);
}
//===============================================
static void GString_clear(GString* _this) {
    assert(_this);
    free(_this->m_data);
    _this->m_data = 0;
    _this->m_size = 0;
}
//===============================================
static void GString_allocate(GString* _this, int _size) {
    assert(_this);
    if(_size < 0) _size = 0;
    _this->clear(_this);
    _this->m_data = (char*)malloc(sizeof(char)*(_size + 1));
    _this->m_data[_size] = '\0';
    _this->m_size = _size;
}
//===============================================
static GString* GString_create(GString* _this, const char* _data) {
    assert(_this);
    int lSize = strlen(_data);
    _this->allocate(_this, lSize);
    memcpy(_this->m_data, _data, _this->m_size);
    return _this;
}
//===============================================
static GString* GString_assign(GString* _this, GString* _data) {
    assert(_this);
    _this->allocate(_this, _data->m_size);
    memcpy(_this->m_data, _data->m_data, _this->m_size);
    _data->clear(_data);
    return _this;
}
//===============================================
static void GString_add(GString* _this, const char* _data) {
    assert(_this);
    int lSize = strlen(_data);
    int lSizeT = _this->m_size + lSize;
    char* lDataT = (char*)malloc(sizeof(char)*(lSizeT + 1));
    memcpy(&lDataT[0], _this->m_data, _this->m_size);
    memcpy(&lDataT[_this->m_size], _data, lSize);
    lDataT[lSizeT] = '\0';
    _this->clear(_this);
    _this->m_data = lDataT;
    _this->m_size = lSizeT;
}
//===============================================
static const char* GString_format(GString* _this, const char* _format, ...) {
    assert(_this);
    va_list lArgs;
    va_start(lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    char* lData = (char*)malloc(sizeof(char)*(lSize + 1));
    vsnprintf(lData, lSize + 1, _format, lArgs);
    va_end(lArgs);
    _this->clear(_this);
    _this->m_data = lData;
    _this->m_size = lSize;
    return _this->m_data;
}
//===============================================
static GVector* GString_split(GString* _this, const char* _data, const char* _sep) {
    assert(_this);
    GVector* lMap = GVector_new();
    GString* lData = GString_new();
    lData->create(lData, _data);

    char* lToken = strtok(lData->m_data, _sep);

    while(lToken) {
        GString* lValue = GString_new();
        lValue->create(lValue, lToken);
        lMap->add(lMap, lValue);
        lToken = strtok(0, _sep);
    }

    lData->delete(lData);
    return lMap;
}
//===============================================
static int GString_isEmpty(GString* _this) {
    assert(_this);
    if(!_this->m_data || !_this->m_size) return 1;
    return 0;
}
//===============================================
static GString* GString_toBase64(GString* _this) {
    assert(_this);
    char* lBuffer = b64_encode(_this->m_data, _this->m_size);
    _this->create(_this, lBuffer);
    free(lBuffer);
    return _this;
}
//===============================================
static GString* GString_toJson(GString* _this) {
    assert(_this);
    if(!_this->isEmpty(_this)) {
        GXml* lDom = GXml_new();
        GString* lData = GString_new();

        lDom->loadXml(lDom, _this->m_data);
        int lCountC1 = lDom->countNode(lDom, lDom, lData->format(lData, "/rdv/datas/data"));

        if(lCountC1) {
            GJson* lJson = GJson_new();
            lJson->createArr(lJson);

            for(int i = 0; i < lCountC1; i++) {
                GXml* lDomC1 = GXml_new();
                GJson* lJsonC1 = GJson_new();

                lJsonC1->m_json = lJson->addArrObj(lJson);
                lDomC1->m_node = lDom->getNode(lDom, lDom, lData->format(lData, "/rdv/datas/data[position()=%d]", i + 1));
                lDomC1->m_node = xmlFirstElementChild(lDomC1->m_node);

                while(1) {
                    if(!lDomC1->m_node) break;
                    const char* lName = lDomC1->m_node->name;
                    const char* lValue = lDomC1->getValue(lDomC1);

                    if(!strcmp(lName, "map")) {
                        int lCountC2 = lDomC1->countNode(lDomC1, lDom, lData->format(lData, "data"));

                        GJson* lJsonC2 = GJson_new();
                        lJsonC2->m_json = lJsonC1->addObjArr(lJsonC1, "map");

                        for(int j = 0; j < lCountC2; j++) {
                            GXml* lDomC2 = GXml_new();
                            GJson* lJsonC3 = GJson_new();

                            lJsonC3->m_json = lJsonC2->addArrObj(lJsonC2);
                            lDomC2->m_node = lDomC1->getNode(lDomC1, lDom, lData->format(lData, "data[position()=%d]", j + 1));
                            lDomC2->m_node = xmlFirstElementChild(lDomC2->m_node);

                            while(1) {
                                if(!lDomC2->m_node) break;
                                const char* lName = lDomC2->m_node->name;
                                const char* lValue = lDomC2->getValue(lDomC2);
                                lJsonC3->addObjData(lJsonC3, lName, lValue);
                                lDomC2->m_node = xmlNextElementSibling(lDomC2->m_node);
                            }

                            lDomC2->delete(lDomC2);
                            lJsonC3->delete(lJsonC3);
                        }

                        lJsonC2->delete(lJsonC2);
                    }
                    else {
                        lJsonC1->addObjData(lJsonC1, lName, lValue);
                    }

                    lDomC1->m_node = xmlNextElementSibling(lDomC1->m_node);
                }

                lDomC1->delete(lDomC1);
                lJsonC1->delete(lJsonC1);
            }

            lData->create(lData, lJson->toString(lJson));
            lJson->delete(lJson);
            return lData;
        }

        lDom->delete(lDom);
        lData->delete(lData);
    }
    return GString_new();
}
//===============================================
static GString* GString_fromBase64(GString* _this) {
    assert(_this);
    char* lBuffer = b64_decode(_this->m_data, _this->m_size);
    _this->create(_this, lBuffer);
    free(lBuffer);
    return _this;
}
//===============================================
static void GString_print(GString* _this) {
    assert(_this);
    printf("%s\n", _this->m_data);
}
//===============================================
