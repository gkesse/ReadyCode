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
GString2 GCode2::getData(const GString2& _code, const GString2& _key) {
    getCode(_code, _key);
    return getValue();
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
    for(int i = 0; i < _map.size(); i++) {
        GObject2* lObj = _map.at(i);
        lObj->serialize(_code);
        lObj->print();
    }
    return true;
}
//===============================================
