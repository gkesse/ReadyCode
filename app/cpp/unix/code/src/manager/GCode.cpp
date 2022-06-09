//===============================================
#include "GCode.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GCode::GCode() : GXml() {

}
//===============================================
GCode::~GCode() {

}
//===============================================
void GCode::createRequest(const std::string& _module, const std::string& _method) {
    addData("request", "module", _module);
    addData("request", "method", _method);
}
//===============================================
std::string GCode::getModule() {
    std::string lData = getItem("request", "module");
    return lData;
}
//===============================================
std::string GCode::getMethod() {
    std::string lData = getItem("request", "method");
    return lData;
}
//===============================================
std::string GCode::getParam(const std::string& _param) {
    std::string lData = getItem("params", _param);
    return lData;
}
//===============================================
std::string GCode::getSession(const std::string& _param) {
    std::string lData = getItem("session", _param);
    return lData;
}
//===============================================
bool GCode::isValidReq() {
    bool lValidReq = true;
    lValidReq &= (getModule() != "");
    lValidReq &= (getMethod() != "");
    return lValidReq;
}
//===============================================
bool GCode::hasCode() {
    queryXPath(sformat("/rdv/datas/data[code]"));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::hasCode(const std::string& _code) {
    queryXPath(sformat("/rdv/datas/data[code='%s']", _code.c_str()));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::hasCode(const std::string& _code, const std::string& _key) {
    queryXPath(sformat("/rdv/datas/data[code='%s']/%s", _code.c_str(), _key.c_str()));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::hasCode(const std::string& _code, int _index) {
    queryXPath(sformat("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code.c_str(), _index + 1));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::hasCode(const std::string& _code, const std::string& _key, int _index) {
    queryXPath(sformat("/rdv/datas/data[code='%s']/map/data[position()=%d]/%s", _code.c_str(), _index + 1, _key.c_str()));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::hasMap(const std::string& _code) {
    queryXPath(sformat("/rdv/datas/data[code='%s']/map", _code.c_str()));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::createCode(const std::string& _code) {
    if(hasCode(_code)) {
        createXNode("/rdv/datas");
        createXNode("data");
        createXNode("code", _code);
    }
    return true;
}
//===============================================
bool GCode::addData(const std::string& _code, const std::string& _key, const std::string& _value, bool _isCData) {
    if(_value == "") return false;
    createCode(_code);
    getCode(_code);
    createXNode(_key, _value, _isCData);
    return true;
}
//===============================================
bool GCode::getCode(const std::string& _code) {
    getXPath(sformat("/rdv/datas/data[code='%s']", _code));
    return true;
}
//===============================================
void GCode::createCode(const std::string& _code, const std::string& _key, int _value, bool _isCData) {
    addData(_code, _key, std::to_string(_value), _isCData);
}
//===============================================
std::string GCode::getItem(const std::string& _code, const std::string& _key) {
    queryXPath(sformat("/rdv/datas/data[code='%s']/%s", _code.c_str(), _key.c_str()));
    getNodeXPath();
    std::string lData = getNodeValue();
    return lData;
}
//===============================================
std::string GCode::getItem(const std::string& _code, const std::string& _key, int _index) {
    queryXPath(sformat("/rdv/datas/data[code='%s']/map/data[position()=%d]/%s", _code.c_str(), _index + 1, _key.c_str()));
    getNodeXPath();
    std::string lData = getNodeValue();
    return lData;
}
//===============================================
int GCode::countItem(const std::string& _code) {
    queryXPath(sformat("/rdv/datas/data[code='%s']/map/data", _code.c_str()));
    int lData = countXPath();
    return lData;
}
//===============================================
bool GCode::loadCode(const std::string& _data, bool _isRoot) {
    if(_data == "") return false;
    createXNode("/rdv/datas");
    loadNode(_data, _isRoot);
    return true;
}
//===============================================
std::string GCode::toStringCode(const std::string& _code) {
    queryXPath(sformat("/rdv/datas/data[code='%s']", _code.c_str()));
    getNodeXPath();
    std::string lData = toStringNode();
    return lData;
}
//===============================================
