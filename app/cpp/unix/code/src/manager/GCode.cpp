//===============================================
#include "GCode.h"
#include "GObject.h"
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
        createXNode("/rdv/datas");
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
bool GCode::createRequest(const GString& _modules, const GString& _method) {
    addData("manager", "module", _modules);
    addData("manager", "method", _method);
    return true;
}
//===============================================
bool GCode::loadData(const GString& _data) {
    if(_data.trim().isEmpty()) return false;
    GCode lDom;
    lDom.loadXml(_data);
    GString lData = lDom.toData();
    createCode();
    loadNode(lData);
    return true;
}
//===============================================
bool GCode::getCode() {
    return getXNode("/rdv/datas");
}
//===============================================
bool GCode::getCode(const GString& _code) {
    return getXNode(GFORMAT("/rdv/datas/data[code='%s']", _code.c_str()));
}
//===============================================
bool GCode::getCode(const GString& _code, const GString& _key) {
    return getXNode(GFORMAT("/rdv/datas/data[code='%s']/%s", _code.c_str(), _key.c_str()));
}
//===============================================
bool GCode::getMap(const GString& _code, int _index) {
    return getXNode(GFORMAT("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code.c_str(), _index + 1));
}
//===============================================
GString GCode::getData(const GString& _code, const GString& _key) {
    if(!getCode(_code, _key)) return "";
    return getValue();
}
//===============================================
bool GCode::getData(const GString& _code, std::vector<GObject*>& _map, GObject* _obj) {
    clearMap(_map);
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
bool GCode::getData(const GString& _code, std::vector<GLog*>& _map, GLog* _obj) {
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
        GLog* lObj = _obj->clone();
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
bool GCode::addData(const GString& _code, const std::vector<GLog*>& _map) {
    if(_map.size() == 0) return false;
    createCode(_code);
    if(!getCode(_code, "map")) {
        createNode("map");
        next();
    }
    for(int i = 0; i < (int)_map.size(); i++) {
        GLog* lObj = _map.at(i);
        GString lData = lObj->serialize(_code);
        GCode lDom;
        lDom.loadXml(lData);
        lData = lDom.toData();
        loadNode(lData);
    }
    return true;
}
//===============================================
bool GCode::addData(const GString& _data) {
    if(_data.trim().isEmpty()) return false;
    GCode lDom;
    lDom.loadXml(_data);
    if(!lDom.getXNode("/rdv/datas/data/code")) return false;
    GString lCode = lDom.getValue();
    if(lCode.isEmpty()) return false;
    if(!lDom.getCode(lCode)) return false;
    if(!getCode(lCode)) {
        loadData(_data);
    }
    else {
        replaceNode(lDom);
    }
    return true;
}
//===============================================
void GCode::clearMap(std::vector<GObject*>& _map) {
    for(int i = 0; i < (int)_map.size(); i++) {
        GObject* lObj = _map.at(i);
        delete lObj;
    }
    _map.clear();
}
//===============================================
int GCode::countMap(const GString& _code) {
    int lData = countNode(GFORMAT("/rdv/datas/data[code='%s']/map/data", _code.c_str()));
    return lData;
}
//===============================================
bool GCode::hasCode() {
    int lCount = countNode(GFORMAT("/rdv/datas/data[code]"));
    return (lCount != 0);
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
GString GCode::toJson() {
    GJson lJson;
    int lState = 0;
    GString lCode;
    lJson.createObject();
    if(getXNode("/rdv/datas")) {
        toJson(m_node, lState, lCode, lJson);
    }
    return lJson.toString();
}
//===============================================
void GCode::toJson(xmlNodePtr _node, int& _state, GString& _code, GJson& _json) {
    for (xmlNodePtr lNode = _node; lNode; lNode = lNode->next) {
        if (lNode->type == XML_ELEMENT_NODE) {
            GString lName = (const char*)lNode->name;
            GString lValue = (const char*)xmlNodeGetContent(lNode);
            if(_state == 0) {
                if(lName == "code") {
                    _code = lValue;
                    _json.pushObject();
                    _json.createObject();
                    _state = 1;
                }
            }
            else if(_state == 1) {
                if(lName == "map") {
                    _json.pushObject();
                    _json.createArray();
                    _state = 2;
                }
                else if(lName == "data") {
                    _json.initChild();
                    _json.popObject();
                    _json.initParent();
                    _json.addObject(_code);
                    _state = 0;
                }
                else {
                    _json.addData(lName, lValue);
                }
            }
            else if(_state == 2) {
                if(lName == "code") {
                    _json.pushObject();
                    _json.createObject();
                    _state = 3;
                }
            }
            else if(_state == 3) {
                if(lName == "data") {
                    if(xmlNextElementSibling(lNode)) {
                        _json.initChild();
                        _json.popObject();
                        _json.initParent();
                        _json.addObject();
                        _state = 2;
                    }
                    else {
                        _json.initChild();
                        _json.popObject();
                        _json.initParent();
                        _json.addObject();

                        _json.initChild();
                        _json.popObject();
                        _json.initParent();
                        _json.addObject("map");

                        _json.initChild();
                        _json.popObject();
                        _json.initParent();
                        _json.addObject(_code);

                        _state = 0;
                    }
                }
                else {
                    _json.addData(lName, lValue);
                    if(!xmlNextElementSibling(lNode)) {
                        if(!xmlNextElementSibling(lNode->parent)) {
                            if(!xmlNextElementSibling(lNode->parent->parent->parent)) {
                                _json.initChild();
                                _json.popObject();
                                _json.initParent();
                                _json.addObject();

                                _json.initChild();
                                _json.popObject();
                                _json.initParent();
                                _json.addObject("map");

                                _json.initChild();
                                _json.popObject();
                                _json.initParent();
                                _json.addObject(_code);

                                _state = 0;
                            }
                        }
                    }
                }
            }
        }
        toJson(lNode->children, _state, _code, _json);
    }
}
//===============================================
