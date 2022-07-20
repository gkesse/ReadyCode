//===============================================
#include "GError.h"
#include "GCode.h"
#include "GLog.h"
//===============================================
GError::GError() : GObject() {
    m_side = "";
    m_msg = "";
}
//===============================================
GError::~GError() {

}
//===============================================
GObject* GError::clone() {
    return new GError;
}
//===============================================
std::string GError::serialize(const std::string& _code) {
    GCode lReq;
    lReq.createDoc();
    lReq.addData(_code, "side", m_side);
    lReq.addData(_code, "msg", m_msg);
    lReq.addData(_code, m_map);
    return lReq.toStringCode(_code);
}
//===============================================
void GError::deserialize(const std::string& _data, const std::string& _code) {
    GCode lReq;
    lReq.loadXml(_data);
    m_side = lReq.getItem(_code, "side");
    m_msg = lReq.getItem(_code, "msg");
    lReq.getItem(_code, m_map, this);
}
//===============================================
std::string GError::deserializer(const std::string& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, m_errors);
    return lDom.toStringData();
}
//===============================================
void GError::addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _error) {
    GLOGI->traceLog(_name, _level, _file, _line, _func, _error);
    m_errors.push_back(_error);
}
//===============================================
void GError::addError(const char* _name, int _level, const char* _file, int _line, const char* _func, GError& _error) {
    GLOGI->traceLog(_name, _level, _file, _line, _func, _error.toString());
    std::vector<std::string>& lErrors = _error.getErrors();
    m_errors.insert(m_errors.end(), lErrors.begin(), lErrors.end());
}
//===============================================
std::string GError::toString() const {
    if(!hasErrors()) return "";
    std::string lErrors = "";
    for(int i = 0; i < (int)m_errors.size(); i++) {
        if(i != 0) lErrors += "\n";
        lErrors += m_errors.at(i);
    }
    return lErrors;
}
//===============================================
bool GError::hasErrors() const {
    return !m_errors.empty();
}
//===============================================
void GError::clearErrors() {
    m_errors.clear();
}
//===============================================
void GError::loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _res) {
    GCode lDom;
    lDom.loadXml(_res);
    int lCount = lDom.countItem("error");
    for(int i = 0; i < lCount; i++) {
        std::string lError = lDom.getItem("error", "msg", i);
        addError(_name, _level, _file, _line, _func, lError);
    }
}
//===============================================
std::vector<std::string>& GError::getErrors() {
    return m_errors;
}
//===============================================
