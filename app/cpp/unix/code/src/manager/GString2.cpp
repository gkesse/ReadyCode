//===============================================
#include "GString2.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GString2::GString2()
: GObject() {
    m_data = "";
}
//===============================================
GString2::GString2(const std::string& _data)
: GObject() {
    m_data = _data;
}
//===============================================
GString2::GString2(const char* _data)
: GObject() {
    m_data = _data;
}
//===============================================
GString2::GString2(int _data)
: GObject(){
    m_data = std::to_string(_data);
}
//===============================================
GString2::GString2(const GString2& _data)
: GObject() {
    m_data = _data.m_data;
}
//===============================================
GString2::~GString2() {

}
//===============================================
GString2& GString2::operator=(const GString2& _data) {
    m_data = _data.m_data;
    return *this;
}
//===============================================
GString2& GString2::operator=(const std::string& _data) {
    m_data = _data;
    return *this;
}
//===============================================
GString2& GString2::operator=(const char* _data) {
    m_data = _data;
    return *this;
}
//===============================================
GString2& GString2::operator=(int _data) {
    m_data = std::to_string(_data);
    return *this;
}
//===============================================
GString2& GString2::operator+=(const GString2& _data) {
    m_data += _data.m_data;
    return *this;
}
//===============================================
GString2& GString2::operator+=(const std::string& _data) {
    m_data += _data;
    return *this;
}
//===============================================
GString2& GString2::operator+=(const char* _data) {
    m_data += _data;
    return *this;
}
//===============================================
GString2& GString2::operator+=(int _data) {
    m_data += std::to_string(_data);
    return *this;
}
//===============================================
bool GString2::operator==(const GString2& _data) {
    bool lEqual = true;
    lEqual &= (m_data == _data.m_data);
    return lEqual;
}
//===============================================
bool GString2::operator==(const std::string& _data) {
    bool lEqual = true;
    lEqual &= (m_data == _data);
    return lEqual;
}
//===============================================
bool GString2::operator==(const char* _data) {
    std::string lData = _data;
    bool lEqual = true;
    lEqual &= (m_data == lData);
    return lEqual;
}
//===============================================
bool GString2::operator==(int _data) {
    std::string lData = std::to_string(_data);
    bool lEqual = true;
    lEqual &= (m_data == lData);
    return lEqual;
}
//===============================================
GString2 operator+(const GString2& _data1, const GString2& _data2) {
    GString2 lData(_data1);
    lData += _data2;
    return lData;
}
//===============================================
std::ostream& operator<<(std::ostream& _os, const GString2& _data) {
    _os << _data.m_data;
    return _os;
}
//===============================================
