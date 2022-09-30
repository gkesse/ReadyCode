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
void GCode::createReq(const GString& _module, const GString& _method) {
    addData("request", "module", _module);
    addData("request", "method", _method);
}
//===============================================
bool GCode::hasCode() {
    queryXPath(GFORMAT("/rdv/datas/data[code]"));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::hasCode(const GString& _code) {
    queryXPath(GFORMAT("/rdv/datas/data[code='%s']", _code.c_str()));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::hasCode(const GString& _code, const GString& _key) {
    queryXPath(GFORMAT("/rdv/datas/data[code='%s']/%s", _code.c_str(), _key.c_str()));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::createCode(const GString& _code) {
    if(!hasCode(_code)) {
        createXNode("/rdv/datas");
        createNode("data");
        createXNode("code", _code);
    }
    return true;
}
//===============================================
bool GCode::addData(const GString& _code, const GString& _key, const GString& _value, bool _isCData) {
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
bool GCode::addData(const GString& _code, const GString& _key, int _value, bool _isCData) {
    GString lData = std::to_string(_value);
    addData(_code, _key, lData, _isCData);
    return true;
}
//===============================================
bool GCode::addData(const GString& _code, const std::vector<GString>& _datas, bool _isCData) {
    if(!_datas.size()) return false;
    createCode(_code);
    getCode(_code);
    createXNode("map");
    for(int i = 0; i < (int)_datas.size(); i++) {
        GString lData = _datas[i];
        saveNode();
        createNode("data");
        setNodeValue(lData, _isCData);
        restoreNode();
    }
    return true;
}
//===============================================
bool GCode::addData(const GString& _code, const std::vector<GObject*>& _datas) {
    if(!_datas.size()) return false;
    createCode(_code);
    getCode(_code);
    createXNode("map");
    for(int i = 0; i < (int)_datas.size(); i++) {
        GObject* lObj = _datas[i];
        lObj->setIsParent(false);
        GString lData = lObj->serialize(_code);
        loadNode(lData);
    }
    return true;
}
//===============================================
bool GCode::getCode(const GString& _code) {
    getXPath(GFORMAT("/rdv/datas/data[code='%s']", _code.c_str()));
    return true;
}
//===============================================
bool GCode::getCode(const GString& _code, const GString& _key) {
    getXPath(GFORMAT("/rdv/datas/data[code='%s']/%s", _code.c_str(), _key.c_str()));
    return true;
}
//===============================================
GString GCode::getItem(const GString& _code, const GString& _key) {
    queryXPath(GFORMAT("/rdv/datas/data[code='%s']/%s", _code.c_str(), _key.c_str()));
    getNodeXPath();
    GString lData = getNodeValue();
    return lData;
}
//===============================================
GString GCode::getItem(const GString& _code, const GString& _key, int _index) {
    getXPath(GFORMAT("/rdv/datas/data[code='%s']/map/data[position()=%d]/%s", _code.c_str(), _index + 1, _key.c_str()));
    GString lData = getNodeValue();
    return lData;
}
//===============================================
bool GCode::getItem(const GString& _code, std::vector<GObject*>& _datas, GObject* _obj) {
    int lCount = countItem(_code);

    for(int i = 0; i < lCount; i++) {
        GString lData = getMap(_code, i);
        GObject* lObj = _obj->clone();
        lObj->deserialize(lData, _code);
        _datas.push_back(lObj);
    }
    return true;
}
//===============================================
GString GCode::getMap(const GString& _code, int _index) {
    getXPath(GFORMAT("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code.c_str(), _index + 1));
    GString lData = toStringNode();
    GCode lDom;
    lDom.createDoc();
    lDom.createXNode("/rdv/datas");
    lDom.loadNode(lData);
    return lDom.toString();
}
//===============================================
int GCode::countItem(const GString& _code) {
    queryXPath(GFORMAT("/rdv/datas/data[code='%s']/map/data", _code.c_str()));
    int lData = countXPath();
    return lData;
}
//===============================================
bool GCode::loadCode(const GString& _data, bool _isRoot) {
    if(_data == "") return false;
    createXNode("/rdv/datas");
    loadNode(_data, _isRoot);
    return true;
}
//===============================================
GString GCode::toStringCode(const GString& _code) {
    queryXPath(GFORMAT("/rdv/datas/data[code='%s']", _code.c_str()));
    getNodeXPath();
    GString lData = toStringNode();
    return lData;
}
//===============================================
GString GCode::toStringData() {
    GString lData = "";
    if(hasCode()) {
        queryXPath(GFORMAT("/rdv/datas/data"));
        int lCount = countXPath();
        for(int i = 0; i < lCount; i++) {
            getNodeXPath(i);
            lData += toStringNode();
        }
    }
    return lData;
}
//===============================================
