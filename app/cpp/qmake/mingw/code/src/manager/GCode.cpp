//===============================================
#include "GCode.h"
#include "GLog.h"
//===============================================
GCode::GCode()
: GXml() {

}
//===============================================
GCode::~GCode() {

}
//===============================================
bool GCode::createCode() {
    if(!getCode()) {
        createNodePath("/rdv/datas");
    }
    return true;
}
//===============================================
bool GCode::createCode(const GString& _code) {
    if(!getCode(_code)) {
        createCode();
        createNode("data");
        next();
        createNode("code");
        next();
        setValue(_code);
        getCode(_code);
    }
    return true;
}
//===============================================
bool GCode::createRequest(const GString& _module, const GString& _method) {
    addData("request", "module", _module);
    addData("request", "method", _method);
    return true;
}
//===============================================
bool GCode::loadData(const GString& _data) {
    if(_data.trim() == "") return true;
    GCode lDom;
    lDom.loadXml(_data);
    GString lData = lDom.toData();
    createCode();
    loadNode(lData);
    return true;
}
//===============================================
bool GCode::getCode() {
    return getNode("/rdv/datas");
}
//===============================================
bool GCode::getCode(const GString& _code) {
    return getNode(GFORMAT("/rdv/datas/data[code='%s']", _code.c_str()));
}
//===============================================
bool GCode::getCode(const GString& _code, const GString& _key) {
    return getNode(GFORMAT("/rdv/datas/data[code='%s']/%s", _code.c_str(), _key.c_str()));
}
//===============================================
bool GCode::getCode(const GString& _code, int _index) {
    return getNode(GFORMAT("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code.c_str(), _index + 1));
}
//===============================================
bool GCode::getMap(const GString& _code, int _index) {
    return getNode(GFORMAT("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code.c_str(), _index + 1));
}
//===============================================
GString GCode::getData(const GString& _code, const GString& _key) {
    if(!getCode(_code, _key)) return "";
    return getValue();
}
//===============================================
GString GCode::getData(const GString& _code, int _index) {
    if(!getCode(_code, _index)) return "";
    return getValue();
}
//===============================================
bool GCode::getData(const GString& _code, std::vector<GObject*>& _map, GObject* _obj) {
    int lCount = countMap(_code);
    for(int i = 0; i < lCount; i++) {
        getMap(_code, i);
        GString lData = toNode();
        lData = GFORMAT("<rdv>%s</rdv>", lData.c_str());
        GCode lDom;
        lDom.createDoc();
        lDom.createCode();
        lDom.loadNode(lData);
        lData = lDom.toString();
        GObject* lObj = _obj->clone();
        lObj->deserialize(lData, _code);
        _map.push_back(lObj);
    }
    return true;
}
//===============================================
bool GCode::addData(const GString& _code, const GString& _key, const GString& _value, bool _isCData) {
    if(_value.isEmpty()) return false;
    if(_value.size() == 1 && _value == "0") return false;
    createCode(_code);
    if(!getCode(_code, _key)) {
        createNode(_key);
        next();
    }
    setValue(_value, _isCData);
    return true;
}
//===============================================
bool GCode::addData(const GString& _code, const std::vector<GObject*>& _map) {
    if(_map.size() == 0) return false;
    createCode(_code);
    if(!getCode(_code, "map")) {
        createNode("map");
        next();
    }
    for(int i = 0; i < (int)_map.size(); i++) {
        GObject* lObj = _map.at(i);
        GString lData = lObj->serialize(_code);
        GCode lDom;
        lDom.loadXml(lData);
        lData = lDom.toData();
        loadNode(lData);
    }
    return true;
}
//===============================================
int GCode::countMap(const GString& _code) {
    int lData = countNode(GFORMAT("/rdv/datas/data[code='%s']/map/data", _code.c_str()));
    return lData;
}
//===============================================
GString GCode::toData() {
    GString lData = "";
    if(getCode()) {
        lData = toNode();
    }
    return lData;
}
//===============================================
