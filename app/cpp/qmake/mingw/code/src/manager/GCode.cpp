//===============================================
#include "GCode.h"
#include "GLog.h"
#include "GUser.h"
//===============================================
GCode::GCode(QObject* _parent) : GXml(_parent) {

}
//===============================================
GCode::GCode(const QString& _code, QObject* _parent) : GXml(_parent) {
    setCode(_code);
}
//===============================================
GCode::~GCode() {

}
//===============================================
void GCode::createRequest(const QString& _module, const QString& _method) {
    createDoc("1.0", "rdv");
    createCode("request", "module", _module);
    createCode("request", "method", _method);
}
//===============================================
void GCode::addParam(const QString& _key, int _value) {
    createCode("params", _key, QString("%1").arg(_value));
}
//===============================================
void GCode::addParam(const QString& _key, const QString& _value) {
    createCode("params", _key, _value);
}
//===============================================
void GCode::addSession(const QString& _key, const QString& _value) {
    createCode("session", _key, _value);
}
//===============================================
void GCode::addPseudo() {
    QString lPseudo = GUSERI->getPseudo();
    addSession("pseudo", lPseudo);
}
//===============================================
QString GCode::getModule() {
    QString lData = getItem("request", "module");
    return lData;
}
//===============================================
QString GCode::getMethod() {
    QString lData = getItem("request", "method");
    return lData;
}
//===============================================
void GCode::setCode(const QString& _code) {
    loadXmlData(_code);
    createXPath();
}
//===============================================
bool GCode::hasCode(const QString& _code) {
    queryXPath(QString("/rdv/datas/data[code='%1']").arg(_code));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::hasCode(const QString& _code, int _index) {
    queryXPath(QString("/rdv/datas/data[code='%1']/map/data[position()=%2]").arg(_code).arg(_index + 1));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::hasCode(const QString& _code, const QString& _key, int _index) {
    queryXPath(QString("/rdv/datas/data[code='%1']/map/data[position()=%2]/%3").arg(_code).arg(_index + 1).arg(_key));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::hasCode(const QString& _code, const QString& _key) {
    queryXPath(QString("/rdv/datas/data[code='%1']/map/data/%2").arg(_code).arg(_key));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
bool GCode::hasMap(const QString& _code) {
    queryXPath(QString("/rdv/datas/data[code='%1']/map").arg(_code));
    int lCount = countXPath();
    return (lCount != 0);
}
//===============================================
void GCode::createCode() {
    createDoc("1.0", "rdv");
}
//===============================================
void GCode::createCode(const QString& _code) {
    createNodePath("/rdv/datas");
    if(!hasCode(_code)) {
        appendNodeGet("data");
        appendNode("code", _code);
    }
    else {
        queryXPath(QString("/rdv/datas/data[code='%1']").arg(_code)).getNodeXPath();
    }
}
//===============================================
void GCode::createCode(const QString& _code, const QString& _key, const QString& _value) {
    if(_value == "") return;
    createCode(_code);
    if(!hasCode(_code, _key)) {
        appendNode(_key, _value);
    }
    else {
        setNodeValue(_key, _value);
    }
}
//===============================================
void GCode::createMap(const QString& _code, const QString& _key, int _value, int _index, bool _isCData) {
    createMap(_code, _key, QString("%1").arg(_value), _index, _isCData);
}
//===============================================
void GCode::createMap(const QString& _code, const QString& _key, const QString& _value, int _index, bool _isCData) {
    createCode(_code);
    if(!hasMap(_code)) {
        appendNodeGet("map");
        appendNodeGet("data");
        setAttribute("i", QString("%1").arg(_index + 1));
        if(_isCData) appendCData(_key, _value);
        else appendNode(_key, _value);
    }
    else if(!hasCode(_code, _index)) {
        queryXPath(QString("/rdv/datas/data[code='%1']/map").arg(_code)).getNodeXPath();
        appendNodeGet("data");
        setAttribute("i", QString("%1").arg(_index + 1));
        if(_isCData) appendCData(_key, _value);
        else appendNode(_key, _value);
    }
    else if(!hasCode(_code, _key, _index)) {
        queryXPath(QString("/rdv/datas/data[code='%1']/map/data[position()=%2]").arg(_code).arg(_index + 1)).getNodeXPath();
        if(_isCData) appendCData(_key, _value);
        else appendNode(_key, _value);
    }
    else {
        queryXPath(QString("/rdv/datas/data[code='%1']/map/data[position()=%2]/%3").arg(_code).arg(_index + 1).arg(_key)).getNodeXPath();
        if(_isCData) setNodeCData(_key, _value);
        else setNodeValue(_key, _value);
    }
}
//===============================================
QString GCode::getItem(const QString& _code, const QString& _key) {
    queryXPath(QString("/rdv/datas/data[code='%1']/%2").arg(_code).arg(_key));
    getNodeXPath();
    QString lData = getNodeValue();
    return lData;
}
//===============================================
QString GCode::getItem(const QString& _code, const QString& _key, int _index, bool _isCData) {
    queryXPath(QString("/rdv/datas/data[code='%1']/map/data[position()=%2]/%3").arg(_code).arg(_index + 1).arg(_key));
    getNodeXPath();
    QString lData = "";
    if(_isCData) lData = getNodeCData();
    else lData = getNodeValue();
    return lData;
}
//===============================================
int GCode::countItem(const QString& _code) {
    queryXPath(QString("/rdv/datas/data[code='%1']/map/data").arg(_code));
    int lData = countXPath();
    return lData;
}
//===============================================
int GCode::countItem(const QString& _code, const QString& _key) {
    queryXPath(QString("/rdv/datas/data[code='%1']/map/data/%2").arg(_code).arg(_key));
    int lData = countXPath();
    return lData;
}
//===============================================
void GCode::loadCode(const QString& _code) {
    if(_code == "") return;
    queryXPath(QString("/rdv/datas"));
    getNodeXPath();
    loadNodeData(_code);
}
//===============================================
QString GCode::toStringCode(const QString& _code) {
    queryXPath(QString("/rdv/datas/data[code='%1']").arg(_code));
    getNodeXPath();
    QString lData = toStringNode();
    return lData;
}
//===============================================
QString GCode::toStringCode(const QString& _code, int _index) {
    queryXPath(QString("/rdv/datas/data[code='%1']/map/data[position()=%2]").arg(_code).arg(_index + 1));
    getNodeXPath();
    QString lData = toStringNode();
    return lData;
}
//===============================================
