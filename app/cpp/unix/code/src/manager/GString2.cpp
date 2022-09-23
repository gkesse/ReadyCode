//===============================================
#include "GString2.h"
#include "GLog.h"
//===============================================
GString2* GString2::m_instance = 0;
//===============================================
GString2::GString2() {

}
//===============================================
GString2::GString2(const std::string& _data) {
    m_data = _data;
}
//===============================================
GString2::GString2(const char* _data) {
    m_data = _data;
}
//===============================================
GString2::GString2(char _data) {
    m_data = _data;
}
//===============================================
GString2::GString2(bool _data) {
    m_data = (_data ? "1" : "0");
}
//===============================================
GString2::GString2(int _data) {
    m_data = std::to_string(_data);
}
//===============================================
GString2::GString2(const GString2& _data) {
    m_data = _data.m_data;
}
//===============================================
GString2::~GString2() {

}
//===============================================
GString2* GString2::Instance() {
    if(m_instance == 0) {
        m_instance = new GString2;
    }
    return m_instance;
}
//===============================================
const char* GString2::c_str() const {
    return m_data.data();
}
//===============================================
const std::string& GString2::data() const {
    return m_data;
}
//===============================================
std::string& GString2::data() {
    return m_data;
}
//===============================================
std::string GString2::getFormat(const char* _format, ...) {
    va_list lArgs;
    va_start (lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    std::vector<char> lData(lSize + 1);
    vsnprintf(lData.data(), lData.size(), _format, lArgs);
    va_end(lArgs);
    return lData.data();
}
//===============================================
GString2 GString2::extract(int _pos, const GString2& _sep) const {
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
    return lWord;
}
//===============================================
int GString2::count(const GString2& _sep) const {
    int lCount = 1;
    for(int i = 0; i < m_data.size(); i++) {
        char lChar = m_data[i];
        if(_sep.isSep(lChar)) {
            lCount++;
        }
    }
    return lCount;
}
//===============================================
bool GString2::isEmpty() const {
    return m_data.empty();
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
int GString2::sepSize(int _pos, const GString2& _sep) const {
    int lSize = 0;
    int lCount = 0;
    for(int i = 0; i < m_data.size(); i++) {
        char lChar = m_data[i];
        lSize++;
        if(_sep.isSep(lChar)) {
            if(lCount == _pos) break;
            lCount++;
        }
    }
    return lSize;
}
//===============================================
GString2 GString2::trim(const GString2& _sep) const {
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
GString2 GString2::substr(int _pos, int _size) const {
    GString2 lData = m_data.substr(_pos, _size);
    return lData;
}
//===============================================
bool GString2::toBool() const {
    return (m_data == "1");
}
//===============================================
int GString2::toInt() const {
    int lData = std::stoi(m_data);
    return lData;
}
//===============================================
bool GString2::toInt(int& _data) const {
    try {
        _data = std::stoi(m_data);
    }
    catch(const std::exception& e) {
        return false;
    }
    return true;
}
//===============================================
void GString2::print() const {
    std::cout << m_data << "\n";
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
GString2& GString2::operator=(bool _data) {
    m_data = (_data ? "1" : "0");
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
bool GString2::operator==(const GString2& _data) const {
    bool lEqual = true;
    lEqual &= (m_data == _data.m_data);
    return lEqual;
}
//===============================================
bool GString2::operator==(const std::string& _data) const {
    bool lEqual = true;
    lEqual &= (m_data == _data);
    return lEqual;
}
//===============================================
bool GString2::operator==(const char* _data) const {
    std::string lData = _data;
    bool lEqual = true;
    lEqual &= (m_data == lData);
    return lEqual;
}
//===============================================
bool GString2::operator==(char _data) const {
    bool lEqual = true;
    lEqual &= (m_data[0] == _data);
    return lEqual;
}
//===============================================
bool GString2::operator==(int _data) const {
    std::string lData = std::to_string(_data);
    bool lEqual = true;
    lEqual &= (m_data == lData);
    return lEqual;
}
//===============================================
bool GString2::operator!=(const GString2& _data) const {
    bool lEqual = true;
    lEqual &= (m_data != _data.m_data);
    return lEqual;
}
//===============================================
bool GString2::operator!=(const std::string& _data) const {
    bool lEqual = true;
    lEqual &= (m_data != _data);
    return lEqual;
}
//===============================================
bool GString2::operator!=(const char* _data) const {
    std::string lData = _data;
    bool lEqual = true;
    lEqual &= (m_data != lData);
    return lEqual;
}
//===============================================
bool GString2::operator!=(char _data) const {
    bool lEqual = true;
    lEqual &= (m_data[0] != _data);
    return lEqual;
}
//===============================================
bool GString2::operator!=(int _data) const {
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
