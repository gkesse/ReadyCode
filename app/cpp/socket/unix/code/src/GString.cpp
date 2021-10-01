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
std::string GString::str() const {
    return m_data;
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
int GString::toChar(char* buffer, int _size) const {
    int i = 0;
    int lSize = size();
    while(1) {
    	if(i >= _size) {break;}
    	if(i >= lSize) {break;}
    	if(m_data[i] == 0) {break;}
        buffer[i] = m_data[i];
        i++;
    }
    buffer[i] = 0;
    return i;
}
//===============================================
int GString::toChar(char* buffer, int index, int _size) const {
    int i = 0;
    int lSize = size();
    while(1) {
    	if(i >= _size) {break;}
    	if(i + index >= lSize) {buffer[i] = 0; return -1;}
    	if(m_data[i + index] == 0) {break;}
        buffer[i] = m_data[i + index];
        i++;
    }
    buffer[i] = 0;
    return i + index;
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
