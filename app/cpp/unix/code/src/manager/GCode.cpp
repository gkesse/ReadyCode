//===============================================
#include "GCode.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GCode::GCode() : GXml() {
    createDoc();
}
//===============================================
GCode::GCode(const std::string& _code) : GXml(_code, false) {

}
//===============================================
GCode::GCode(const std::string& _version, const std::string& _nodeRoot) : GXml(_version, _nodeRoot) {
    createDoc();
}
//===============================================
GCode::~GCode() {

}
//===============================================
void GCode::createRequest(const std::string& _module, const std::string& _method) {
    createCode("request", "module", _module);
    createCode("request", "method", _method);
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
bool GCode::isValidReq() {
    bool lValidReq = true;
    lValidReq &= (getModule() != "");
    lValidReq &= (getMethod() != "");
    return lValidReq;
}
//===============================================
bool GCode::hasCode(const std::string& _code) {
    queryXPath(sformat("/rdv/datas/data[code='%s']", _code.c_str()));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::hasCode(const std::string& _code, const std::string& _key) {
    queryXPath(sformat("/rdv/datas/data[code='%s']/map/data/%s", _code.c_str(), _key.c_str()));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
void GCode::createCode(const std::string& _code) {
    createNodePath("/rdv/datas");
    if(!hasCode(_code)) {
        appendNodeGet("data");
        appendNode("code", _code);
    }
    else {
        queryXPath(sformat("/rdv/datas/data[code='%s']", _code.c_str())).getNodeXPath();
    }
}
//===============================================
void GCode::createCode(const std::string& _code, const std::string& _key, const std::string& _value) {
    createCode(_code);
    if(!hasCode(_code, _key)) {
        appendNode(_key, _value);
    }
    else {
        setNodeValue(_key, _value);
    }
}
//===============================================
void GCode::createMap(const std::string& _code, const std::string& _key, const std::string& _value) {
    createCode(_code);
    if(!hasCode(_code, _key)) {
        appendNodeGet("map");
        appendNodeGet("data");
        appendNode(_key, _value);
    }
    else {
        getNode("map");
        appendNodeGet("data");
        appendNode(_key, _value);
    }
}
//===============================================
std::string GCode::getItem(const std::string& _code, const std::string& _key) {
    queryXPath(sformat("/rdv/datas/data[code='%s']/%s", _code.c_str(), _key.c_str()));
    getNodeXPath();
    std::string lData = getNodeValue();
    return lData;
}
//===============================================
std::string GCode::getItem(const std::string& _code, int _index, const std::string& _key) {
    queryXPath(sformat("/rdv/datas/data[code='%s']/map/data[position()=%d]/%s", _code.c_str(), _index + 1, _key.c_str()));
    getNodeXPath();
    std::string lData = getNodeValue();
    return lData;
}
//===============================================
int GCode::countItem(const std::string& _code, const std::string& _key) {
    queryXPath(sformat("/rdv/datas/data[code='%s']/map/data/%s", _code.c_str(), _key.c_str()));
    int lData = countXPath();
    return lData;
}
//===============================================
