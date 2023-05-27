//===============================================
#include "GCode.h"
#include "GXml.h"
//===============================================
static void GCode_delete(GCode* _this);
static xmlNodePtr GCode_createDatas(GCode* _this);
static xmlNodePtr GCode_createCode(GCode* _this, const char* _code);
static void GCode_addData(GCode* _this, const char* _code, const char* _key, const char* _value);
//===============================================
GCode* GCode_new() {
    GCode* lObj = (GCode*)malloc(sizeof(GCode));
    lObj->m_dom = GXml_new();

    lObj->delete = GCode_delete;
    lObj->createDatas = GCode_createDatas;
    lObj->createCode = GCode_createCode;
    lObj->addData = GCode_addData;
    return lObj;
}
//===============================================
static void GCode_delete(GCode* _this) {
    assert(_this);
    _this->m_dom->delete(_this->m_dom);
    free(_this);
}
//===============================================
static xmlNodePtr GCode_createDatas(GCode* _this) {
    assert(_this);
    GXml* lDom = _this->m_dom;
    GString* lString = GString_new();
    xmlNodePtr lNode = lDom->getNode(lDom, lDom, lString->format(lString, "/rdv/datas"));
    if(!lNode) {
        lNode = lDom->createNode(lDom, lDom, lString->format(lString, "/rdv/datas"), "");
    }
    lString->delete(lString);
    return lNode;
}
//===============================================
static xmlNodePtr GCode_createCode(GCode* _this, const char* _code) {
    assert(_this);
    GXml* lDom = _this->m_dom;
    GString* lString = GString_new();
    GXml* lNode = GXml_new();
    lNode->m_node = lDom->getNode(lDom, lDom, lString->format(lString, "/rdv/datas/data[code='%s']", _code));
    if(!lNode->m_node) {
        lNode->m_node = _this->createDatas(_this);
        lNode->m_node = lNode->addObj(lNode, "data");
        lNode->addData(lNode, "code", _code);
    }
    xmlNodePtr lNodeC = lNode->m_node;
    lString->delete(lString);
    lNode->delete(lNode);
    return lNodeC;
}
//===============================================
static void GCode_addData(GCode* _this, const char* _code, const char* _key, const char* _value) {
    assert(_this);
    GXml* lDom = _this->m_dom;
    GXml* lNode = GXml_new();
    GString* lString = GString_new();
    lNode->m_node = lDom->getNode(lDom, lDom, lString->format(lString, "/rdv/datas/data[code='%s']/%s", _code, _key));
    if(!lNode->m_node) {
        lNode->m_node = _this->createCode(_this, _code);
        lNode->addData(lNode, _key, _value);
    }
    else {
        lNode->setValue(lNode, _value);
    }
    lNode->delete(lNode);
    lString->delete(lString);
}
//===============================================
