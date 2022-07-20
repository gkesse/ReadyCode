//===============================================
#include "GCode.h"
#include "GLog.h"
#include "GUser.h"
//===============================================
GCode::GCode(QObject* _parent)
: GXml(_parent) {

}
//===============================================
GCode::~GCode() {

}
//===============================================
void GCode::createReq(const QString& _module, const QString& _method) {
    addData("request", "module", _module);
    addData("request", "method", _method);
}
//===============================================
bool GCode::hasCode() {
    queryXPath(QString("/rdv/datas/data[code]"));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::hasCode(const QString& _code) {
    queryXPath(QString("/rdv/datas/data[code='%1']").arg(_code));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::hasCode(const QString& _code, const QString& _key) {
    queryXPath(QString("/rdv/datas/data[code='%1']/%2").arg(_code).arg(_key));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::createCode(const QString& _code) {
    if(!hasCode(_code)) {
        createXNode("/rdv/datas");
        createNode("data");
        createXNode("code", _code);
    }
    return true;
}
//===============================================
bool GCode::addData(const QString& _code, const QString& _key, const QString& _value, bool _isCData) {
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
bool GCode::addData(const QString& _code, const QString& _key, int _value, bool _isCData) {
    QString lData = QString("%1").arg(_value);
    addData(_code, _key, lData, _isCData);
    return true;
}
//===============================================
bool GCode::addData(const QString& _code, const QVector<QString>& _datas, bool _isCData) {
    if(!_datas.size()) return false;
    createCode(_code);
    getCode(_code);
    createXNode("map");
    for(int i = 0; i < (int)_datas.size(); i++) {
        QString lData = _datas[i];
        saveNode();
        createNode("data");
        setNodeValue(lData, _isCData);
        restoreNode();
    }
    return true;
}
//===============================================
bool GCode::addData(const QString& _code, QVector<GObject*>& _datas) {
    if(!_datas.size()) return false;
    createCode(_code);
    getCode(_code);
    createXNode("map");
    for(int i = 0; i < (int)_datas.size(); i++) {
        GObject* lObj = _datas[i];
        QString lData = lObj->serialize(false, _code);
        loadNode(lData);
    }
    clearMap(_datas);
    return true;
}
//===============================================
bool GCode::getCode(const QString& _code) {
    getXPath(QString("/rdv/datas/data[code='%1']").arg(_code));
    return true;
}
//===============================================
bool GCode::getCode(const QString& _code, const QString& _key) {
    getXPath(QString("/rdv/datas/data[code='%1']/%2").arg(_code).arg(_key));
    return true;
}
//===============================================
QString GCode::getItem(const QString& _code, const QString& _key) {
    queryXPath(QString("/rdv/datas/data[code='%1']/%2").arg(_code).arg(_key));
    getNodeXPath();
    QString lData = getNodeValue();
    return lData;
}
//===============================================
QString GCode::getItem(const QString& _code, int _index) {
    getXPath(QString("/rdv/datas/data[code='%1']/map/data[position()=%2]").arg(_code).arg(_index + 1));
    QString lData = getNodeValue();
    return lData;
}
//===============================================
QString GCode::getItem(const QString& _code, const QString& _key, int _index) {
    getXPath(QString("/rdv/datas/data[code='%1']/map/data[position()=%2]/%3").arg(_code).arg(_index + 1).arg(_key));
    QString lData = getNodeValue();
    return lData;
}
//===============================================
QString GCode::getItem(const QString& _code, const QString& _category, const QString& _key) {
    int lCount = countItem(_code);
    for(int i = 0; i < lCount; i++) {
        QString lCategory = getItem(_code, "category", i);
        QString lData = getItem(_code, _key, i);
        if(lCategory == _category) {
            return lData;
        }
    }
    return "";
}
//===============================================
bool GCode::getItem(const QString& _code, QVector<GObject*>& _datas, GObject* _obj) {
    int lCount = countItem(_code);

    for(int i = 0; i < lCount; i++) {
        QString lData = getMap(_code, i);
        GObject* lObj = _obj->clone();
        lObj->deserialize(lData, _code);
        _datas.push_back(lObj);
    }
    return true;
}
//===============================================
QString GCode::getMap(const QString& _code, int _index) {
    getXPath(QString("/rdv/datas/data[code='%1']/map/data[position()=%2]").arg(_code).arg(_index + 1));
    QString lData = toStringNode();
    GCode lDom;
    lDom.createDoc();
    lDom.createXNode("/rdv/datas");
    lDom.loadNode(lData);
    return lDom.toString();
}
//===============================================
int GCode::countItem(const QString& _code) {
    queryXPath(QString("/rdv/datas/data[code='%1']/map/data").arg(_code));
    int lData = countXPath();
    return lData;
}
//===============================================
bool GCode::loadCode(const QString& _data, bool _isRoot) {
    if(_data == "") return false;
    createXNode("/rdv/datas");
    loadNode(_data, _isRoot);
    return true;
}
//===============================================
QString GCode::toStringCode(const QString& _code) {
    queryXPath(QString("/rdv/datas/data[code='%1']").arg(_code));
    getNodeXPath();
    QString lData = toStringNode();
    return lData;
}
//===============================================
QString GCode::toStringData() {
    QString lData = "";
    if(hasCode()) {
        queryXPath(QString("/rdv/datas/data"));
        int lCount = countXPath();
        for(int i = 0; i < lCount; i++) {
            getNodeXPath(i);
            lData += toStringNode();
        }
    }
    return lData;
}
//===============================================
