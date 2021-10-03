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
void GString::setData(int data) {
    m_data = std::to_string(data);
}
//===============================================
void GString::setData(const std::string& data) {
    m_data = data;
}
//===============================================
void GString::setData(const char* data, int size) {
    clear();
    for(int i = 0; i < size; i++) {
        m_data += data[i];
    }
}
//===============================================
void GString::addData(const char* data, int size) {
    for(int i = 0; i < size; i++) {
        m_data += data[i];
    }
}
//===============================================
void GString::clear() {
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
void GString::toChar(char* buffer) const {
    int i = 0;
    while(m_data[i] != 0) {
        buffer[i] = m_data[i];
        i++;
    }
    buffer[i] = 0;
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
