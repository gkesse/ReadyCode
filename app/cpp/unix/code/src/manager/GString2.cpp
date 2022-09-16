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
GString2::GString2(char _data)
: GObject(){
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
const char* GString2::c_str() const {
    return m_data.data();
}
//===============================================
std::string GString2::str() const {
    return m_data;
}
//===============================================
GString2 GString2::extract(int _pos, const GString2& _sep) {
    GString2 lWord = "";
    int lPos = 0;
    for(int i = 0; i < m_data.size(); i++) {
        char lChar = m_data[i];
        if(_sep.isSep(lChar)) {
            if(lPos == _pos) return lWord;
            lWord = "";
            lPos++;
        }
        else {
            lWord += lChar;
        }
    }
    return "";
}
//===============================================
bool GString2::isSep(char _char) const {
    for(int i = 0; i < m_data.size(); i++) {
        if(m_data[i] == _char) return true;
    }
    return false;
}
//===============================================
int GString2::size() const {
    return m_data.size();
}
//===============================================
bool GString2::startBy(const GString2& _data) const {
    if(m_data.size() == 0) return false;
    if(_data.size() == 0) return false;
    if(m_data.size() < _data.size()) return false;
    int i = 0;
    for(; i < _data.size(); i++) {
        if(m_data[i] != _data[i]) return false;
    }
    return true;
}
//===============================================
GString2 GString2::trim(const GString2& _sep) {
    int lStartPos = 0;
    int lEndPos = m_data.size() - 1;
    GString2 lData = "";
    for(int i = 0; i < m_data.size(); i++) {
        char lChar = m_data[i];
        if(!_sep.isSep(lChar)) break;
        lStartPos++;
    }
    for(int i = m_data.size() - 1; i >= 0 ; i--) {
        char lChar = m_data[i];
        if(!_sep.isSep(lChar)) break;
        lEndPos--;
    }
    for(int i = lStartPos; i <= lEndPos; i++) {
        char lChar = m_data[i];
        lData += lChar;
    }
    return lData;
}
//===============================================
int GString2::toInt() const {
    int lInt = std::stoi(m_data);
    return lInt;
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
GString2& GString2::operator=(char _data) {
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
GString2& GString2::operator+=(char _data) {
    m_data += _data;
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
bool GString2::operator==(char _data) {
    bool lEqual = true;
    lEqual &= (m_data[0] == _data);
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
bool GString2::operator!=(const GString2& _data) {
    bool lEqual = true;
    lEqual &= (m_data != _data.m_data);
    return lEqual;
}
//===============================================
bool GString2::operator!=(const std::string& _data) {
    bool lEqual = true;
    lEqual &= (m_data != _data);
    return lEqual;
}
//===============================================
bool GString2::operator!=(const char* _data) {
    std::string lData = _data;
    bool lEqual = true;
    lEqual &= (m_data != lData);
    return lEqual;
}
//===============================================
bool GString2::operator!=(char _data) {
    bool lEqual = true;
    lEqual &= (m_data[0] != _data);
    return lEqual;
}
//===============================================
bool GString2::operator!=(int _data) {
    std::string lData = std::to_string(_data);
    bool lEqual = true;
    lEqual &= (m_data == lData);
    return lEqual;
}
//===============================================
char& GString2::operator[](int _index) {
    return m_data[_index];
}
//===============================================
const char& GString2::operator[](int _index) const {
    return m_data[_index];
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
