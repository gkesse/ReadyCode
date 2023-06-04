//===============================================
#include "GString.h"
//===============================================
GString::GString() {
    m_data = 0;
    m_size = 0;
}
//===============================================
GString::GString(const char* _data, int _size) {
    create(_data, _size);
}
//===============================================
GString::GString(const char* _data) {
    create(_data, strlen(_data));
}
//===============================================
GString::GString(const std::string& _data) {
    create(_data.data(), _data.size());
}
//===============================================
GString::GString(const GString& _data) {
    create(_data.m_data, _data.m_size);
}
//===============================================
GString::~GString() {
    clear();
}
//===============================================
void GString::clear() {
    free(m_data);
    m_data = 0;
    m_size = 0;
}
//===============================================
void GString::create(const char* _data, int _size) {
    m_size = _size;
    m_data = new char[m_size + 1];
    m_data[m_size] = '\0';
    memcpy(m_data, _data, m_size);
}
//===============================================
bool GString::isEmpty() const {
    if(!m_data || !m_size) return true;
    return false;
}
//===============================================
const char* GString::c_str() const {
    return m_data;
}
//===============================================
void GString::print() const {
    printf("%s\n", m_data);
}
//===============================================
GString& GString::operator=(const char* _data) {
    clear();
    create(_data, strlen(_data));
    return *this;
}
//===============================================
GString& GString::operator=(const std::string& _data) {
    clear();
    create(_data.data(), _data.size());
    return *this;
}
//===============================================
GString& GString::operator=(const GString& _data) {
    clear();
    create(_data.m_data, _data.m_size);
    return *this;
}
//===============================================
bool GString::operator==(const char* _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator==(const std::string& _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator==(const GString& _data) const {
    if(m_size != _data.m_size) return false;
    for(int i = 0; i < m_size; i++) {
        if(m_data[i] != _data.m_data[i]) return false;
    }
    return true;
}
//===============================================
