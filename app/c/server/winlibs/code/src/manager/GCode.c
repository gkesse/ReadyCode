//===============================================
#include "GCode.h"
#include "GXml.h"
#include "GVector.h"
//===============================================
static void GCode_delete(GCode* _this);
static xmlNodePtr GCode_createDatas(GCode* _this);
static xmlNodePtr GCode_createCode(GCode* _this, const char* _code);
static void GCode_addData(GCode* _this, const char* _code, const char* _key, const char* _value);
static const char* GCode_getData(GCode* _this, const char* _code, const char* _key);
static void GCode_addMap(GCode* _this, const char* _code, GVector* _map);
static void GCode_addLog(GCode* _this, const char* _code, GVector* _map);
static void GCode_getLog(GCode* _this, const char* _code, GVector* _map, GLog* _obj);
static GString* GCode_toDatas(GCode* _this);
static void GCode_print(GCode* _this);
//===============================================
GCode* GCode_new() {
    GCode* lObj = (GCode*)malloc(sizeof(GCode));
    lObj->m_dom = GXml_new();

    lObj->delete = GCode_delete;
    lObj->createDatas = GCode_createDatas;
    lObj->createCode = GCode_createCode;
    lObj->addData = GCode_addData;
    lObj->getData = GCode_getData;
    lObj->addMap = GCode_addMap;
    lObj->addLog = GCode_addLog;
    lObj->getLog = GCode_getLog;
    lObj->toDatas = GCode_toDatas;
    lObj->print = GCode_print;
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
static const char* GCode_getData(GCode* _this, const char* _code, const char* _key) {
    assert(_this);
    GXml* lDom = _this->m_dom;
    GXml* lNode = GXml_new();
    GString* lString = GString_new();
    lNode->m_node = lDom->getNode(lDom, lDom, lString->format(lString, "/rdv/datas/data[code='%s']/%s", _code, _key));
    const char* lData = "";
    if(lNode->m_node) {
        lData = lNode->getValue(lNode);
    }
    lNode->delete(lNode);
    lString->delete(lString);
    return lData;
}
//===============================================
static void GCode_addMap(GCode* _this, const char* _code, GVector* _map) {
    assert(_this);
    GXml* lDom = _this->m_dom;
    int lSize = _map->size(_map);
    if(!lSize) return;
    GXml* lNode = GXml_new();
    GString* lString = GString_new();
    GString* lData = GString_new();

    lNode->m_node = lDom->getNode(lDom, lDom, lString->format(lString, "/rdv/datas/data[code='%s']/map", _code));
    if(!lNode->m_node) {
        lNode->m_node = _this->createCode(_this, _code);
        lNode->m_node = lNode->addObj(lNode, "map");
    }

    for(int i = 0; i < lSize; i++) {
        GLog* lObj = _map->get(_map, i);
        lData->assign(lData, lObj->serialize(lObj));
        GCode* lDomD = GCode_new();
        lDomD->m_dom->loadXml(lDomD->m_dom, lData->m_data);
        lData->assign(lData, lDomD->toDatas(lDomD));
        lNode->loadNode(lNode, lData->m_data);
    }

    lNode->delete(lNode);
    lString->delete(lString);
    lData->delete(lData);
}
//===============================================
static void GCode_addLog(GCode* _this, const char* _code, GVector* _map) {
    assert(_this);
    GXml* lDom = _this->m_dom;

    int lSize = _map->size(_map);
    if(!lSize) return;

    GXml* lNode = GXml_new();
    GString* lString = GString_new();
    GString* lData = GString_new();

    lNode->m_node = lDom->getNode(lDom, lDom, lString->format(lString, "/rdv/datas/data[code='%s']/map", _code));
    if(!lNode->m_node) {
        lNode->m_node = _this->createCode(_this, _code);
        lNode->m_node = lNode->addObj(lNode, "map");
    }

    for(int i = 0; i < lSize; i++) {
        GLog* lObj = _map->get(_map, i);
        lData->assign(lData, lObj->serialize(lObj));
        GCode* lDomD = GCode_new();
        lDomD->m_dom->loadXml(lDomD->m_dom, lData->m_data);
        lData->assign(lData, lDomD->toDatas(lDomD));
        lNode->loadNode(lNode, lData->m_data);
    }

    lNode->delete(lNode);
    lString->delete(lString);
    lData->delete(lData);
}
//===============================================
static void GCode_getLog(GCode* _this, const char* _code, GVector* _map, GLog* _obj) {
    assert(_this);
    GXml* lDom = _this->m_dom;
    GString* lString = GString_new();

    int lCount = lDom->countNode(lDom, lDom, lString->format(lString, "/rdv/datas/data[code='%s']/map/data", _code));
    if(!lCount) {
        lString->delete(lString);
        return;
    }

    GXml* lNode = GXml_new();
    GString* lData = GString_new();

    for(int i = 0; i < lCount; i++) {
        lNode->m_node = lDom->getNode(lDom, lDom, lString->format(lString, "/rdv/datas/data[code='%s']/map/data[position()=%d]", _code, i + 1));
        lData->assign(lData, lNode->toNode(lNode, lDom));
        lData->format(lData, "<rdv>%s</rdv>", lData->m_data);

        GCode* lDomC = GCode_new();
        lDomC->m_dom->createDoc(lDomC->m_dom);
        lNode->m_node = lDomC->createDatas(lDomC);
        lNode->loadNode(lNode, lData->m_data);
        lData->assign(lData, lDomC->m_dom->toString(lDomC->m_dom));

        GLog* lObj = _obj->clone(_obj);
        lObj->deserialize(lObj, lData->m_data);
        _map->add(_map, lObj);
    }

    lNode->delete(lNode);
    lString->delete(lString);
    lData->delete(lData);
}
//===============================================
static GString* GCode_toDatas(GCode* _this) {
    assert(_this);
    GXml* lDom = _this->m_dom;
    GString* lData = GString_new();
    GXml* lNode = GXml_new();

    lNode->m_node = lNode->getNode(lNode, lDom, lData->format(lData, "/rdv/datas"));
    if(lNode->m_node) {
        lData->assign(lData, lNode->toNode(lNode, lDom));
    }
    else {
        lData->create(lData, "");
    }

    lNode->delete(lNode);
    return lData;
}
//===============================================
static void GCode_print(GCode* _this) {
    assert(_this);
    _this->m_dom->print(_this->m_dom);
}
//===============================================
