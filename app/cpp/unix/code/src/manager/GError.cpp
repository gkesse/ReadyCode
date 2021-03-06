//===============================================
#include "GError.h"
#include "GCode.h"
#include "GLog.h"
//===============================================
GError::GError() : GObject() {

}
//===============================================
GError::~GError() {

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
    GCode lRes(_res);
    int lCount = lRes.countItem("error");
    for(int i = 0; i < lCount; i++) {
        std::string lError = lRes.getItem("error", "msg", i);
        addError(_name, _level, _file, _line, _func, lError);
    }
}
//===============================================
std::vector<std::string>& GError::getErrors() {
    return m_errors;
}
//===============================================
