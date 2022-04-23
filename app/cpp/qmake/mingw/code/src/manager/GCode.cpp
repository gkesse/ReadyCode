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
bool GCode::hasCode(const QString& _code, const QString& _key) {
    queryXPath(QString("/rdv/datas/data[code='%1']/map/data/%2").arg(_code).arg(_key));
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
    createCode(_code);
    if(!hasCode(_code, _key)) {
        appendNode(_key, _value);
    }
    else {
        setNodeValue(_key, _value);
    }
}
//===============================================
void GCode::createMap(const QString& _code, const QString& _key, const QString& _value) {
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
QString GCode::getItem(const QString& _code, const QString& _key) {
    queryXPath(QString("/rdv/datas/data[code='%1']/%2").arg(_code).arg(_key));
    getNodeXPath();
    QString lData = getNodeValue();
    return lData;
}
//===============================================
QString GCode::getItem(const QString& _code, int _index, const QString& _key) {
    queryXPath(QString("/rdv/datas/data[code='%1']/map/data[position()=%2]/%3").arg(_code).arg(_index + 1).arg(_key));
    getNodeXPath();
    QString lData = getNodeValue();
    return lData;
}
//===============================================
int GCode::countItem(const QString& _code, const QString& _key) {
    queryXPath(QString("/rdv/datas/data[code='%1']/map/data/%2").arg(_code).arg(_key));
    int lData = countXPath();
    return lData;
}
//===============================================
