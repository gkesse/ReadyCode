//===============================================
#include "GCalculator.h"
//===============================================
static void GCalculator_delete(GCalculator* _this);
static GObject* GCalculator_clone(GObject* _this);
static GString* GCalculator_serialize(GObject* _this);
static void GCalculator_deserialize(GObject* _this, const char* _data);
static void GCalculator_run(GCalculator* _this, const char* _data);
static void GCalculator_onRunCalculator(GCalculator* _this, const char* _data);
//===============================================
GCalculator* GCalculator_new() {
    GCalculator* lObj = (GCalculator*)malloc(sizeof(GCalculator));
    lObj->m_mgr = GManager_new();
    lObj->m_obj = GObject_new();
    lObj->m_expression = GString_new();
    lObj->m_result = GString_new();

    lObj->delete = GCalculator_delete;
    lObj->run = GCalculator_run;
    lObj->onRunCalculator = GCalculator_onRunCalculator;

    lObj->m_obj->clone = GCalculator_clone;
    lObj->m_obj->serialize = GCalculator_serialize;
    lObj->m_obj->deserialize = GCalculator_deserialize;
    lObj->m_obj->m_child = lObj;
    return lObj;
}
//===============================================
static void GCalculator_delete(GCalculator* _this) {
    assert(_this);
    _this->m_mgr->delete(_this->m_mgr);
    _this->m_obj->delete(_this->m_obj);
    _this->m_expression->delete(_this->m_expression);
    _this->m_result->delete(_this->m_result);
    free(_this);
}
//===============================================
static GObject* GCalculator_clone(GObject* _this) {
    assert(_this);
    return GCalculator_new()->m_obj;
}
//===============================================
static GString* GCalculator_serialize(GObject* _this) {
    assert(_this);
    const char* lCode = "calculator";
    GCode* lDom = GCode_new();
    lDom->m_dom->createDoc(lDom->m_dom);
    GCalculator* lObj = (GCalculator*)_this->m_child;

    lDom->addData(lDom, lCode, "expression", lObj->m_expression->toBase64(lObj->m_expression)->m_data);
    lDom->addData(lDom, lCode, "result", lObj->m_result->m_data);
    lDom->addMap(lDom, lCode, _this->m_map);

    lDom->delete(lDom);
    return lDom->m_dom->toString(lDom->m_dom);
}
//===============================================
static void GCalculator_deserialize(GObject* _this, const char* _data) {
    assert(_this);
    const char* lCode = "calculator";
    GCode* lDom = GCode_new();
    lDom->m_dom->loadXml(lDom->m_dom, _data);
    GCalculator* lObj = (GCalculator*)_this->m_child;

    lObj->m_expression->create(lObj->m_expression, lDom->getData(lDom, lCode, "expression"))->fromBase64(lObj->m_expression)->m_data;
    lObj->m_result->create(lObj->m_result, lDom->getData(lDom, lCode, "result"));
    lDom->getMap(lDom, lCode, _this->m_map, _this);

    lDom->delete(lDom);
}
//===============================================
static void GCalculator_run(GCalculator* _this, const char* _data) {
    assert(_this);
    GManager* lMgr = _this->m_mgr;
    GLog* lLog = _this->m_obj->m_logs;
    lMgr->m_obj->deserialize(lMgr->m_obj, _data);
    _this->m_obj->deserialize(_this->m_obj, _data);

    if(!strcmp(lMgr->m_method, "")) {
        lLog->addError(lLog, "Le module est obligatoire.");
    }
    else if(!strcmp(lMgr->m_method, "run_calculator")) {
        _this->onRunCalculator(_this, _data);
    }
    else {
        lLog->addError(lLog, "Le module est inconnu.");
    }
}
//===============================================
static void GCalculator_onRunCalculator(GCalculator* _this, const char* _data) {
    assert(_this);
    GLog* lLog = _this->m_obj->m_logs;

    if(!strcmp(_this->m_expression->m_data, "")) {
        lLog->addError(lLog, "L'expression est vide.");
        return;
    }

    double lResult = te_interp(_this->m_expression->m_data, 0);
    _this->m_result->format(_this->m_result, "%.2f", lResult);
}
//===============================================
