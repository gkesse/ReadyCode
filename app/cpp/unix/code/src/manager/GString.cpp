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
int GString::readData(std::string& _data, int _index, int _size) const {
	_data.clear();
    if(_index >= _size) return 0;
    _data = m_data.substr(_index, _size);
    return _data.size();
}
//===============================================
void GString::printData() const {
    std::cout << m_data;
}
//===============================================
std::ostream& operator<<(std::ostream& _os, const GString& _data) {
	_data.printData();
    return _os;
}
//===============================================
