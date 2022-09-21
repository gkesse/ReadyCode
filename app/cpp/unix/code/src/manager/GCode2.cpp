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
bool GCode2::getCode() const {
    return getNode("/rdv/datas");
}
//===============================================
bool GCode2::getCode(const GString2& _code) const {
    return getNode(sformat("/rdv/datas/data[code='%s']", _code.c_str()));
}
//===============================================
bool GCode2::getCode(const GString2& _code, const GString2& _key) const {
    return getNode(sformat("/rdv/datas/data[code='%s']/%s", _code.c_str(), _key.c_str()));
}
//===============================================
GString2 GCode2::getData(const GString2& _code, const GString2& _key) const {
    getCode(_code, _key);
    GString2 lData =
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
