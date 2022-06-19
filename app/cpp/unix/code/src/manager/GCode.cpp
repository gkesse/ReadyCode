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
void GCode::createReq(const std::string& _module, const std::string& _method) {
    addData("request", "module", _module);
    addData("request", "method", _method);
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
bool GCode::createCode(const std::string& _code) {
    if(!hasCode(_code)) {
        createXNode("/rdv/datas");
        createNode("data");
        createXNode("code", _code);
    }
    return true;
}
//===============================================
bool GCode::addData(const std::string& _code, const std::string& _key, const std::string& _value, bool _isCData) {
    if(_value == "") return false;
    createCode(_code);
    if(!hasCode(_code, _key)) {
        getCode(_code);
        createXNode(_key, _value, _isCData);
    }
    else {
        getCode(_code, _key);
        setNodeValue(_value, _isCData);
    }
    return true;
}
//===============================================
bool GCode::addData(const std::string& _code, const std::string& _key, int _value, bool _isCData) {
    std::string lData = std::to_string(_value);
    addData(_code, _key, lData, _isCData);
    return true;
}
//===============================================
bool GCode::addData(const std::string& _code, const std::vector<std::string>& _datas, bool _isCData) {
    if(!_datas.size()) return false;
    createCode(_code);
    getCode(_code);
    createXNode("map");
    for(int i = 0; i < (int)_datas.size(); i++) {
        std::string lData = _datas[i];
        saveNode();
        createNode("data");
        setNodeValue(lData, _isCData);
        restoreNode();
    }
    return true;
}
//===============================================
bool GCode::addData(const std::string& _code, const std::vector<GObject*>& _datas) {
    if(!_datas.size()) return false;
    createCode(_code);
    getCode(_code);
    createXNode("map");
    for(int i = 0; i < (int)_datas.size(); i++) {
        GObject* lObj = _datas[i];
        std::string lData = lObj->serialize(_code);
        loadNode(lData);
    }
    clearMap();
    return true;
}
//===============================================
bool GCode::getCode(const std::string& _code) {
    getXPath(sformat("/rdv/datas/data[code='%s']", _code.c_str()));
    return true;
}
//===============================================
bool GCode::getCode(const std::string& _code, const std::string& _key) {
    getXPath(sformat("/rdv/datas/data[code='%s']/%s", _code.c_str(), _key.c_str()));
    return true;
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
std::string GCode::toStringData() {
    std::string lData = "";
    if(hasCode()) {
        queryXPath(sformat("/rdv/datas/data"));
        int lCount = countXPath();
        for(int i = 0; i < lCount; i++) {
            getNodeXPath(i);
            lData += toStringNode();
        }
    }
    return lData;
}
//===============================================
