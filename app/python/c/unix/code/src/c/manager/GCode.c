//===============================================
#include "GCode.h"
#include "GVector.h"
#include "GString.h"
#include "GObject.h"
#include "GLog.h"
#include "GFunctions.h"
//===============================================
static void GCode_delete(GCode* _this);
static xmlNodePtr GCode_createDatas(GCode* _this);
static xmlNodePtr GCode_createCode(GCode* _this, const char* _code);
static void GCode_addData(GCode* _this, const char* _code, const char* _key, const char* _value);
static GString* GCode_getData(GCode* _this, const char* _code, const char* _key);
static void GCode_loadData(GCode* _this, const char* _data);
static void GCode_addMap(GCode* _this, const char* _code, GVector* _map);
static void GCode_getMap(GCode* _this, const char* _code, GVector* _map, GObject* _obj);
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
    lObj->loadData = GCode_loadData;
    lObj->addMap = GCode_addMap;
    lObj->getMap = GCode_getMap;
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

    xmlNodePtr lNode = lDom->getNode(lDom, lDom, sformat("/rdv/datas"));
    if(!lNode) {
        lNode = lDom->createNode(lDom, lDom, sformat("/rdv/datas"), "");
    }

    return lNode;
}
//===============================================
static xmlNodePtr GCode_createCode(GCode* _this, const char* _code) {
    assert(_this);
    GXml* lDom = _this->m_dom;
    GXml* lNode = GXml_new();
    lNode->m_node = lDom->getNode(lDom, lDom, sformat("/rdv/datas/data[code='%s']", _code));
    if(!lNode->m_node) {
        lNode->m_node = _this->createDatas(_this);
        lNode->m_node = lNode->addObj(lNode, "data");
        lNode->addData(lNode, "code", _code);
    }
    xmlNodePtr lNodeC = lNode->m_node;
    lNode->delete(lNode);
    return lNodeC;
}
//===============================================
static void GCode_addData(GCode* _this, const char* _code, const char* _key, const char* _value) {
    assert(_this);
    if(!_value) return;
    if(!strcmp(_value, "")) return;

    GXml* lDom = _this->m_dom;
    GXml* lNode = GXml_new();

    lNode->m_node = lDom->getNode(lDom, lDom, sformat("/rdv/datas/data[code='%s']/%s", _code, _key));

    if(!lNode->m_node) {
        lNode->m_node = _this->createCode(_this, _code);
        lNode->addData(lNode, _key, _value);
    }
    else {
        lNode->setValue(lNode, _value);
    }

    lNode->delete(lNode);
}
//===============================================
static GString* GCode_getData(GCode* _this, const char* _code, const char* _key) {
    assert(_this);
    GXml* lDom = _this->m_dom;
    GXml* lNode = GXml_new();
    lNode->m_node = lDom->getNode(lDom, lDom, sformat("/rdv/datas/data[code='%s']/%s", _code, _key));
    GString* lData = GString_new();
    if(lNode->m_node) {
        lData->assign(lData, lNode->getValue(lNode));
    }
    lNode->delete(lNode);
    return lData;
}
//===============================================
static void GCode_loadData(GCode* _this, const char* _data) {
    assert(_this);
    GCode* lDom = _this;
    GCode* lDomC = GCode_new();
    GXml* lNode = GXml_new();
    GXml* lNodeC = GXml_new();
    GString* lData = GString_new();

    lNode->m_node = lDom->m_dom->getNode(lDom->m_dom, lDom->m_dom, sformat("/rdv/datas"));
    if(lNode->m_node) {
        lDomC->m_dom->loadXml(lDomC->m_dom, _data);
        lNodeC->m_node = lDomC->m_dom->getNode(lDomC->m_dom, lDomC->m_dom, sformat("/rdv/datas"));
        if(lNodeC->m_node) {
            lData->assign(lData, lNodeC->toNode(lNodeC, lDomC->m_dom));
            lNode->loadNode(lNode, lData->m_data);
        }
    }

    lNode->delete(lNode);
    lDomC->delete(lDomC);
    lNodeC->delete(lNodeC);
    lData->delete(lData);
}
//===============================================
static void GCode_addMap(GCode* _this, const char* _code, GVector* _map) {
    assert(_this);
    GXml* lDom = _this->m_dom;

    int lSize = _map->size(_map);
    if(!lSize) return;

    GXml* lNode = GXml_new();
    GString* lData = GString_new();

    lNode->m_node = lDom->getNode(lDom, lDom, sformat("/rdv/datas/data[code='%s']/map", _code));
    if(!lNode->m_node) {
        lNode->m_node = _this->createCode(_this, _code);
        lNode->m_node = lNode->addObj(lNode, "map");
    }

    for(int i = 0; i < lSize; i++) {
        GObject* lObj = _map->get(_map, i);
        lData->assign(lData, lObj->serialize(lObj));
        GCode* lDomD = GCode_new();
        lDomD->m_dom->loadXml(lDomD->m_dom, lData->m_data);
        lData->assign(lData, lDomD->toDatas(lDomD));
        lNode->loadNode(lNode, lData->m_data);
    }

    lNode->delete(lNode);
    lData->delete(lData);
}
//===============================================
static void GCode_getMap(GCode* _this, const char* _code, GVector* _map, GObject* _obj) {
    assert(_this);
    GXml* lDom = _this->m_dom;

    _obj->clear(_obj);

    int lCount = lDom->countNode(lDom, lDom, sformat("/rdv/datas/data[code='%s']/map/data", _code));
    if(!lCount) {
        return;
    }

    GXml* lNode = GXml_new();
    GString* lData = GString_new();

    for(int i = 0; i < lCount; i++) {
        lNode->m_node = lDom->getNode(lDom, lDom, sformat("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code, i + 1));
        lData->assign(lData, lNode->toNode(lNode, lDom));
        char* lBuffer = sformat("<rdv>%s</rdv>", lData->m_data);

        GCode* lDomC = GCode_new();
        lDomC->m_dom->createDoc(lDomC->m_dom);
        lNode->m_node = lDomC->createDatas(lDomC);
        lNode->loadNode(lNode, lBuffer);
        lData->assign(lData, lDomC->m_dom->toString(lDomC->m_dom));

        GObject* lObj = _obj->clone(_obj);
        lObj->deserialize(lObj, lData->m_data);
        _map->add(_map, lObj);
    }

    lNode->delete(lNode);
    lData->delete(lData);
}
//===============================================
static void GCode_addLog(GCode* _this, const char* _code, GVector* _map) {
    assert(_this);
    GXml* lDom = _this->m_dom;

    int lSize = _map->size(_map);
    if(!lSize) return;

    GXml* lNode = GXml_new();
    GString* lData = GString_new();

    lNode->m_node = lDom->getNode(lDom, lDom, sformat("/rdv/datas/data[code='%s']/map", _code));
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
        lDomD->delete(lDomD);
    }

    lNode->delete(lNode);
    lData->delete(lData);
}
//===============================================
static void GCode_getLog(GCode* _this, const char* _code, GVector* _map, GLog* _obj) {
    assert(_this);
    GXml* lDom = _this->m_dom;

    _obj->clear(_obj);

    int lCount = lDom->countNode(lDom, lDom, sformat("/rdv/datas/data[code='%s']/map/data", _code));
    if(!lCount) {
        return;
    }

    GXml* lNode = GXml_new();
    GString* lData = GString_new();

    for(int i = 0; i < lCount; i++) {
        lNode->m_node = lDom->getNode(lDom, lDom, sformat("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code, i + 1));
        lData->assign(lData, lNode->toNode(lNode, lDom));
        char* lBuffer = sformat("<rdv>%s</rdv>", lData->m_data);

        GCode* lDomC = GCode_new();
        lDomC->m_dom->createDoc(lDomC->m_dom);
        lNode->m_node = lDomC->createDatas(lDomC);
        lNode->loadNode(lNode, lBuffer);
        lData->assign(lData, lDomC->m_dom->toString(lDomC->m_dom));

        GLog* lObj = _obj->clone(_obj);
        lObj->deserialize(lObj, lData->m_data);
        _map->add(_map, lObj);
    }

    lNode->delete(lNode);
    lData->delete(lData);
}
//===============================================
static GString* GCode_toDatas(GCode* _this) {
    assert(_this);
    GXml* lDom = _this->m_dom;
    GString* lData = GString_new();
    GXml* lNode = GXml_new();

    lNode->m_node = lNode->getNode(lNode, lDom, sformat("/rdv/datas"));
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