//===============================================
#include "GString.h"
#include "GLog.h"
//===============================================
GString* GString::m_instance = 0;
//===============================================
GString::GString() {

}
//===============================================
GString::GString(const QString& _data) {
    m_data = _data.toStdString();
}
//===============================================
GString::GString(const std::string& _data) {
    m_data = _data.c_str();
}
//===============================================
GString::GString(const char* _data) {
    m_data = _data;
}
//===============================================
GString::GString(char _data) {
    m_data = _data;
}
//===============================================
GString::GString(int _data) {
    m_data = std::to_string(_data);
}
//===============================================
GString::GString(const GString& _data) {
    m_data = _data.m_data;
}
//===============================================
GString::~GString() {

}
//===============================================
GString* GString::Instance() {
    if(m_instance == 0) {
        m_instance = new GString;
    }
    return m_instance;
}
//===============================================
const char* GString::c_str() const {
    return m_data.data();
}
//===============================================
const std::string& GString::data() const {
    return m_data;
}
//===============================================
std::string& GString::data() {
    return m_data;
}
//===============================================
GString GString::extract(int _pos, const GString& _sep) const {
    GString lWord = "";
    int lPos = 0;
    for(int i = 0; i < (int)m_data.size(); i++) {
        char lChar = m_data.at(i);
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
int GString::count(const GString& _sep) const {
    int lCount = 1;
    for(int i = 0; i < (int)m_data.size(); i++) {
        char lChar = m_data.at(i);
        if(_sep.isSep(lChar)) {
            lCount++;
        }
    }
    return lCount;
}
//===============================================
bool GString::isEmpty() const {
    return m_data.empty();
}
//===============================================
bool GString::isSep(char _char) const {
    for(int i = 0; i < (int)m_data.size(); i++) {
        if(m_data[i] == _char) return true;
    }
    return false;
}
//===============================================
int GString::size() const {
    return (int)m_data.size();
}
//===============================================
bool GString::startBy(const GString& _data) const {
    if((int)m_data.size() == 0) return false;
    if(_data.size() == 0) return false;
    if((int)m_data.size() < _data.size()) return false;
    int i = 0;
    for(; i < _data.size(); i++) {
        if(m_data[i] != _data[i]) return false;
    }
    return true;
}
//===============================================
int GString::sepSize(int _pos, const GString& _sep) const {
    int lSize = 0;
    int lCount = 0;
    for(int i = 0; i < (int)m_data.size(); i++) {
        char lChar = m_data.at(i);
        lSize++;
        if(_sep.isSep(lChar)) {
            if(lCount == _pos) break;
            lCount++;
        }
    }
    return lSize;
}
//===============================================
GString GString::trim(const GString& _sep) const {
    int lStartPos = 0;
    int lEndPos = (int)m_data.size() - 1;
    GString lData = "";
    for(int i = 0; i < (int)m_data.size(); i++) {
        char lChar = m_data.at(i);
        if(!_sep.isSep(lChar)) break;
        lStartPos++;
    }
    for(int i = (int)m_data.size() - 1; i >= 0 ; i--) {
        char lChar = m_data.at(i);
        if(!_sep.isSep(lChar)) break;
        lEndPos--;
    }
    for(int i = lStartPos; i <= lEndPos; i++) {
        char lChar = m_data.at(i);
        lData += lChar;
    }
    return lData;
}
//===============================================
GString GString::substr(int _pos, int _size) const {
    GString lData = m_data.substr(_pos, _size);
    return lData;
}
//===============================================
bool GString::toBool() const {
    return (m_data == "1");
}
//===============================================
int GString::toInt() const {
    int lData = std::stoi(m_data);
    return lData;
}
//===============================================
bool GString::toInt(int& _data) const {
    try {
        _data = std::stoi(m_data);
    }
    catch(const std::exception& e) {
        return false;
    }
    return true;
}
//===============================================
QString GString::toQString() const {
    return m_data.data();
}
//===============================================
GString GString::getFormat(const char* _format, ...) {
    va_list lArgs;
    va_start (lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    std::vector<char> lData(lSize + 1);
    vsnprintf(lData.data(), lData.size(), _format, lArgs);
    va_end(lArgs);
    return lData.data();
}
//===============================================
void GString::print() const {
    printf("%s\n", m_data.c_str());
}
//===============================================
GString& GString::operator=(const GString& _data) {
    m_data = _data.m_data;
    return *this;
}
//===============================================
GString& GString::operator=(const QString& _data) {
    m_data = _data.toStdString();
    return *this;
}
//===============================================
GString& GString::operator=(const std::string& _data) {
    m_data = _data.c_str();
    return *this;
}
//===============================================
GString& GString::operator=(const char* _data) {
    m_data = _data;
    return *this;
}
//===============================================
GString& GString::operator=(char _data) {
    m_data = _data;
    return *this;
}
//===============================================
GString& GString::operator=(int _data) {
    m_data = std::to_string(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(const GString& _data) {
    m_data += _data.m_data;
    return *this;
}
//===============================================
GString& GString::operator+=(const QString& _data) {
    m_data += _data.toStdString();
    return *this;
}
//===============================================
GString& GString::operator+=(const std::string& _data) {
    m_data += _data.c_str();
    return *this;
}
//===============================================
GString& GString::operator+=(const char* _data) {
    m_data += _data;
    return *this;
}
//===============================================
GString& GString::operator+=(int _data) {
    m_data += std::to_string(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(char _data) {
    m_data += _data;
    return *this;
}
//===============================================
bool GString::operator==(const GString& _data) const {
    bool lEqual = true;
    lEqual &= (m_data == _data.m_data);
    return lEqual;
}
//===============================================
bool GString::operator==(const QString& _data) const {
    bool lEqual = true;
    lEqual &= (m_data == _data.toStdString());
    return lEqual;
}
//===============================================
bool GString::operator==(const std::string& _data) const {
    bool lEqual = true;
    lEqual &= (m_data == _data.c_str());
    return lEqual;
}
//===============================================
bool GString::operator==(const char* _data) const {
    std::string lData = _data;
    bool lEqual = true;
    lEqual &= (m_data == lData);
    return lEqual;
}
//===============================================
bool GString::operator==(char _data) const {
    bool lEqual = true;
    lEqual &= (m_data[0] == _data);
    return lEqual;
}
//===============================================
bool GString::operator==(int _data) const {
    std::string lData = std::to_string(_data);
    bool lEqual = true;
    lEqual &= (m_data == lData);
    return lEqual;
}
//===============================================
bool GString::operator!=(const GString& _data) const {
    bool lEqual = true;
    lEqual &= (m_data != _data.m_data);
    return lEqual;
}
//===============================================
bool GString::operator!=(const QString& _data) const {
    bool lEqual = true;
    lEqual &= (m_data != _data.toStdString());
    return lEqual;
}
//===============================================
bool GString::operator!=(const std::string& _data) const {
    bool lEqual = true;
    lEqual &= (m_data != _data.c_str());
    return lEqual;
}
//===============================================
bool GString::operator!=(const char* _data) const {
    std::string lData = _data;
    bool lEqual = true;
    lEqual &= (m_data != lData);
    return lEqual;
}
//===============================================
bool GString::operator!=(char _data) const {
    bool lEqual = true;
    lEqual &= (m_data.at(0) != _data);
    return lEqual;
}
//===============================================
bool GString::operator!=(int _data) const {
    std::string lData = std::to_string(_data);
    bool lEqual = true;
    lEqual &= (m_data == lData);
    return lEqual;
}
//===============================================
char& GString::operator[](int _index) {
    return m_data[_index];
}
//===============================================
const char& GString::operator[](int _index) const {
    return m_data[_index];
}
//===============================================
GString operator+(const GString& _data1, const GString& _data2) {
    GString lData(_data1);
    lData += _data2;
    return lData;
}
//===============================================
std::ostream& operator<<(std::ostream& _os, const GString& _data) {
    _os << _data.m_data;
    return _os;
}
//===============================================
