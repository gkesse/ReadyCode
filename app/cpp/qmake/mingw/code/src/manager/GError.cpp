//===============================================
#include "GError.h"
#include "GCode.h"
//===============================================
GError::GError(QObject* _parent) : GObject(_parent) {

}
//===============================================
GError::~GError() {

}
//===============================================
void GError::addError(const QString& _error) {
    m_errors.push_back(_error);
}
//===============================================
QString GError::toString() const {
    if(!hasErrors()) return "";
    QString lErrors = "";
    for(int i = 0; i < m_errors.size(); i++) {
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
void GError::loadErrors(const QString& _res) {
    GCode lRes;
    lRes.loadXmlData(_res);
    lRes.createXPath();
    int lCount = lRes.countItem("error", "msg");
    for(int i = 0; i < lCount; i++) {
        QString lError = lRes.getItem("error", i, "msg");
        addError(lError);
    }
}
//===============================================
QVector<QString>& GError::getErrors() {
    return m_errors;
}
//===============================================
