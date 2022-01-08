//===============================================
#include "GString.h"
//===============================================
GString::GString() {
    m_data = "";
}
//===============================================
GString::~GString() {

}
//===============================================
void GString::data(int _data) {
    m_data = std::to_string(_data);
}
//===============================================
void GString::data(const std::string& _data) {
    m_data = _data;
}
//===============================================
void GString::data(const char* _data) {
    clearData();
    int lSize = strlen(_data);
    for(int i = 0; i < lSize; i++) {
        m_data += _data[i];
    }
}
//===============================================
void GString::data(const char* _data, int _size) {
    clearData();
    for(int i = 0; i < _size; i++) {
        m_data += _data[i];
    }
}
//===============================================
std::string GString::data() const {
    return m_data;
}
//===============================================
void GString::addData(const char* _data) {
    int lSize = strlen(_data);
    for(int i = 0; i < lSize; i++) {
        m_data += _data[i];
    }
}
//===============================================
void GString::addData(const char* _data, int _size) {
    for(int i = 0; i < _size; i++) {
        m_data += _data[i];
    }
}
//===============================================
void GString::clearData() {
    m_data.clear();
}
//===============================================
int GString::size() const {
    return m_data.size();
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
void GString::print() const {
    std::cout << m_data;
}
//===============================================
std::ostream& operator<<(std::ostream& os, const GString& obj) {
    obj.print();
    return os;
}
//===============================================
