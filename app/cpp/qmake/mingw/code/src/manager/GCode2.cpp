//===============================================
#include "GCode2.h"
#include "GLog.h"
//===============================================
GCode2::GCode2()
: GXml2() {

}
//===============================================
GCode2::~GCode2() {

}
//===============================================
bool GCode2::createCode() {
    if(!getCode()) {
        createNodePath("/rdv/datas");
    }
    return true;
}
//===============================================
bool GCode2::createCode(const GString& _code) {
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
bool GCode2::createRequest(const GString& _module, const GString& _method) {
    addData("request", "module", _module);
    addData("request", "method", _method);
    return true;
}
//===============================================
bool GCode2::loadData(const GString& _data) {
    if(_data.trim() == "") return true;
    GCode2 lDom;
    lDom.loadXml(_data);
    GString lData = lDom.toData();
    loadNode(lData);
    return true;
}
//===============================================
bool GCode2::getCode() {
    return getNode("/rdv/datas");
}
//===============================================
bool GCode2::getCode(const GString& _code) {
    return getNode(sformat("/rdv/datas/data[code='%s']", _code.c_str()));
}
//===============================================
bool GCode2::getCode(const GString& _code, const GString& _key) {
    return getNode(sformat("/rdv/datas/data[code='%s']/%s", _code.c_str(), _key.c_str()));
}
//===============================================
bool GCode2::getMap(const GString& _code, int _index) {
    return getNode(sformat("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code.c_str(), _index + 1));
}
//===============================================
GString GCode2::getData(const GString& _code, const GString& _key) {
    getCode(_code, _key);
    return getValue();
}
//===============================================
bool GCode2::getData(const GString& _code, std::vector<GObject2*>& _map, GObject2* _obj) {
    clearMap(_map);
    int lCount = countMap(_code);
    for(int i = 0; i < lCount; i++) {
        getMap(_code, i);
        GString lData = toNode();
        lData = sformat("<rdv>%s</rdv>", lData.c_str());
        GCode2 lDom;
        lDom.createDoc();
        lDom.createCode();
        lDom.loadNode(lData);
        lData = lDom.toString();
        GObject2* lObj = _obj->clone();
        lObj->deserialize(lData, _code);
        _map.push_back(lObj);
    }
    return true;
}
//===============================================
bool GCode2::addData(const GString& _code, const GString& _key, const GString& _value, bool _isCData) {
    createCode(_code);
    if(!getCode(_code, _key)) {
        createNode(_key);
        next();
    }
    setValue(_value, _isCData);
    return true;
}
//===============================================
bool GCode2::addData(const GString& _code, const std::vector<GObject2*>& _map) {
    if(_map.size() == 0) return false;
    createCode(_code);
    if(!getCode(_code, "map")) {
        createNode("map");
        next();
    }
    for(int i = 0; i < (int)_map.size(); i++) {
        GObject2* lObj = _map.at(i);
        GString lData = lObj->serialize(_code);
        GCode2 lDom;
        lDom.loadXml(lData);
        lData = lDom.toData();
        loadNode(lData);
    }
    return true;
}
//===============================================
int GCode2::countMap(const GString& _code) {
    int lData = countNode(sformat("/rdv/datas/data[code='%s']/map/data", _code.c_str()));
    return lData;
}
//===============================================
GString GCode2::toData() {
    GString lData = "";
    if(getCode()) {
        lData = toNode();
    }
    return lData;
}
//===============================================
