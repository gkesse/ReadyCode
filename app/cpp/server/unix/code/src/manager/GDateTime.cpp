//===============================================
#include "GDateTime.h"
//===============================================
GDateTime::GDateTime() {
    m_isEmpty = true;
}
//===============================================
GDateTime::GDateTime(const datetime& _obj)
: datetime(_obj) {
    m_isEmpty = true;
}
//===============================================
GDateTime::GDateTime(datetime&& _obj) noexcept
: datetime(_obj) {
    m_isEmpty = true;
}
//===============================================
GDateTime::GDateTime(const GDateTime& _obj)
: datetime(_obj) {
    m_isEmpty = _obj.m_isEmpty;
}
//===============================================
GDateTime::~GDateTime() {

}
//===============================================
bool GDateTime::isEmpty() const {
    return m_isEmpty;
}
//===============================================
bool GDateTime::toParse(const GString& _data) {
    try {
        *this = jed_utils::datetime::parse("yyyy/MM/dd HH:mm:ss", _data.c_str());
        m_isEmpty = false;
    }
    catch(...) {
        m_isEmpty = true;
    }
    return true;
}
//===============================================
GString GDateTime::toString() const {
    if(isEmpty()) return "";
    try {
        return to_string();
    }
    catch (...) {}
    return "";
}
//===============================================
