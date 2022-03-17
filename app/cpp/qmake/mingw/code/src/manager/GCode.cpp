//===============================================
#include "GCode.h"
#include "GLog.h"
//===============================================
GCode::GCode(QObject* _parent) : GXml(_parent) {

}
//===============================================
GCode::~GCode() {

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
void GCode::createMap(const QString& _code, const QString& _key, const QString& _name, const QString& _value) {
    createCode(_code);
    if(!hasCode(_code, _key)) {
        appendNodeGet(_key);
        appendNode(_name, _value);
    }
    else {
        getNode(_key);
        appendNode(_name, _value);
    }
}
//===============================================
