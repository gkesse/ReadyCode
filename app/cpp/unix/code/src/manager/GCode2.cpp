//===============================================
#include "GCode2.h"
#include "GLog.h"
#include "GFormat.h"
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
bool GCode2::createCode(const GString2& _code) {
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
bool GCode2::getCode() {
    return getNode("/rdv/datas");
}
//===============================================
bool GCode2::getCode(const GString2& _code) {
    return getNode(sformat("/rdv/datas/data[code='%s']", _code.c_str()));
}
//===============================================
bool GCode2::getCode(const GString2& _code, const GString2& _key) {
    return getNode(sformat("/rdv/datas/data[code='%s']/%s", _code.c_str(), _key.c_str()));
}
//===============================================
bool GCode2::getMap(const GString2& _code, int _index) {
    return getNode(sformat("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code.c_str(), _index + 1));
}
//===============================================
GString2 GCode2::getData(const GString2& _code, const GString2& _key) {
    getCode(_code, _key);
    return getValue();
}
//===============================================
bool GCode2::getData(const GString2& _code, std::vector<GObject2*>& _map) {
    clearMap(_map);
    int lCount = countMap(_code);
    for(int i = 0; i < lCount; i++) {
        getMap(_code, i);
        GString2 lData = toNode();
        lData.print();
    }
    return true;
}
//===============================================
bool GCode2::addData(const GString2& _code, const GString2& _key, const GString2& _value, bool _isCData) {
    createCode(_code);
    if(!getCode(_code, _key)) {
        createNode(_key);
        next();
    }
    setValue(_value, _isCData);
    return true;
}
//===============================================
bool GCode2::addData(const GString2& _code, const std::vector<GObject2*>& _map) {
    if(_map.size() == 0) return false;
    createCode(_code);
    if(!getCode(_code, "map")) {
        createNode("map");
        next();
    }
    for(int i = 0; i < _map.size(); i++) {
        GObject2* lObj = _map.at(i);
        GString2 lData = lObj->serialize(_code);
        GCode2 lDom;
        lDom.loadXml(lData);
        lData = lDom.toData();
        loadNode(lData);
    }
    return true;
}
//===============================================
int GCode2::countMap(const GString2& _code) {
    int lData = countNode(sformat("/rdv/datas/data[code='%1']/map/data", _code.c_str()));
    return lData;
}
//===============================================
GString2 GCode2::toData() {
    GString2 lData = "";
    if(getCode()) {
        lData = toNode();
    }
    return lData;
}
//===============================================
