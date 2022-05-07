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
void GCode::createReq(const std::string& _module, const std::string& _method) {
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
void GCode::createCode() {
    createNodePath("/rdv/datas");
}
//===============================================
void GCode::createCode(const std::string& _code) {
    createCode();
    if(!hasCode(_code)) {
        appendNodeGet("data");
        appendNode("code", _code);
    }
    else {
        queryXPath(sformat("/rdv/datas/data[code='%s']", _code.c_str())).getNodeXPath();
    }
}
//===============================================
void GCode::createCode(const std::string& _code, const std::string& _key, const std::string& _value, bool _isCData) {
    createCode(_code);
    if(!hasCode(_code, _key)) {
        if(!_isCData) appendNode(_key, _value);
        else appendCData(_key, _value);
    }
    else {
        if(!_isCData) setNodeValue(_key, _value);
        else setNodeCData(_key, _value);
    }
}
//===============================================
void GCode::createCode(const std::string& _code, const std::string& _key, int _value, bool _isCData) {
    createCode(_code, _key, std::to_string(_value), _isCData);
}
//===============================================
void GCode::createMap(const std::string& _code, const std::string& _key, int _value, int _index, bool _isCData) {
    createMap(_code, _key, std::to_string(_value), _index, _isCData);
}
//===============================================
void GCode::createMap(const std::string& _code, int _value, int _index, bool _isCData) {
    createMap(_code, std::to_string(_value), _index, _isCData);
}
//===============================================
void GCode::createMap(const std::string& _code, const std::string& _value, int _index, bool _isCData) {
    createCode(_code);
    if(!hasMap(_code)) {
        appendNodeGet("map");
        appendNodeGet("data");
        setAttribute("i", std::to_string(_index + 1));
        if(_isCData) setNodeCData(_value);
        else setNodeValue(_value);
    }
    else if(!hasCode(_code, _index)) {
        queryXPath(sformat("/rdv/datas/data[code='%s']/map", _code.c_str())).getNodeXPath();
        appendNodeGet("data");
        setAttribute("i", std::to_string(_index + 1));
        if(_isCData) setNodeCData(_value);
        else setNodeValue(_value);
    }
    else {
        queryXPath(sformat("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code.c_str(), _index + 1)).getNodeXPath();
        if(_isCData) setNodeCData(_value);
        else setNodeValue(_value);
    }
}
//===============================================
void GCode::createMap(const std::string& _code, const std::string& _key, const std::string& _value, int _index, bool _isCData) {
    createCode(_code);
    if(!hasMap(_code)) {
        appendNodeGet("map");
        appendNodeGet("data");
        setAttribute("i", std::to_string(_index + 1));
        if(_isCData) appendCData(_key, _value);
        else appendNode(_key, _value);
    }
    else if(!hasCode(_code, _index)) {
        queryXPath(sformat("/rdv/datas/data[code='%s']/map", _code.c_str())).getNodeXPath();
        appendNodeGet("data");
        setAttribute("i", std::to_string(_index + 1));
        if(_isCData) appendCData(_key, _value);
        else appendNode(_key, _value);
    }
    else if(!hasCode(_code, _key, _index)) {
        queryXPath(sformat("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code.c_str(), _index + 1)).getNodeXPath();
        if(_isCData) appendCData(_key, _value);
        else appendNode(_key, _value);
    }
    else {
        queryXPath(sformat("/rdv/datas/data[code='%s']/map/data[position()=%d]/%s", _code.c_str(), _index + 1, _key.c_str())).getNodeXPath();
        if(_isCData) setNodeCData(_value);
        else setNodeValue(_value);
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
void GCode::loadCode(const std::string& _code) {
    if(_code == "") return;
    createCode();
    getNodeXPath();
    loadNodeData(_code);
}
//===============================================
std::string GCode::toStringCode(const std::string& _code) {
    queryXPath(sformat("/rdv/datas/data[code='%s']", _code.c_str()));
    getNodeXPath();
    std::string lData = toStringNode();
    return lData;
}
//===============================================
