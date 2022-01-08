//===============================================
#include "GString.h"
//===============================================
GString::GString() {
    m_data = "";
}
//===============================================
GString::GString(const std::string& _data) {
    m_data = _data;
}
//===============================================
GString::GString(int _data) {
    m_data = std::to_string(_data);
}
//===============================================
GString::GString(const char* _data, int _size) {
    m_data = "";
    for(int i = 0; i < _size; i++) {
        m_data += _data[i];
    }
}
//===============================================
GString::GString(const GString& _data) {
    m_data = _data.m_data;
}
//===============================================
GString::~GString() {

}
//===============================================
void GString::addData(const char* _data, int _size) {
    for(int i = 0; i < _size; i++) {
        m_data += _data[i];
    }
}
//===============================================
void GString::clearData() {
    m_data = "";
}
//===============================================
std::string GString::getData() const {
    return m_data;
}
//===============================================
const char* GString::c_str() const {
    return m_data.c_str();
}
//===============================================
void GString::toChar(char* _buffer, int _size) const {
    int i = 0;
    while(1) {
        if(i >= _size) break;
        if(m_data[i] == 0) break;
        _buffer[i] = m_data[i];
        i++;
    }
    _buffer[i] = 0;
}
//===============================================
int GString::toChar(char* _buffer, int _index, int _size) const {
    int i = 0;
    while(1) {
        if(i >= _size) break;
        if(m_data[i + _index] == 0) break;
        _buffer[i] = m_data[i + _index];
        i++;
    }
    _buffer[i] = 0;
    return i;
}
//===============================================
GString& GString::operator+=(const GString& _d) {
    m_data += _d.m_data;
    return *this;
}
//===============================================
GString operator+(const GString& _d1, const GString& _d2) {
    GString d(_d1);
    d += _d2;
    return d;
}
//===============================================
std::ostream& operator<<(std::ostream& _os, const GString& _d) {
    _os << _d.m_data;
    return _os;
}
//===============================================
