//===============================================
#include "GString.h"
//===============================================
GString::GString() : GObject() {
    m_data = "";
}
//===============================================
GString::GString(int _data) : GObject() {
    m_data = std::to_string(_data);
}
//===============================================
GString::GString(const std::string& _data) : GObject() {
    m_data = _data;
}
//===============================================
GString::GString(const GString& _data) : GObject() {
    m_data = _data.m_data;
}
//===============================================
GString::~GString() {

}
//===============================================
std::string GString::getData() const {
    return m_data;
}
//===============================================
const char* GString::getChar() const {
    return m_data.c_str();
}
//===============================================
int GString::getSize() const {
    return m_data.size();
}
//===============================================
void GString::addData(const std::string& _data) {
    m_data += _data;
}
//===============================================
void GString::clearData() {
    m_data.clear();
}
//===============================================
