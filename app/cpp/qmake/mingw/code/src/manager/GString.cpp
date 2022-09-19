//===============================================
#include "GString.h"
#include "GLog.h"
//===============================================
GString::GString() {

}
//===============================================
GString::GString(const QString& _data) {
    m_data = _data;
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
    m_data = QString("%1").arg(_data);
}
//===============================================
GString::GString(const GString& _data) {
    m_data = _data.m_data;
}
//===============================================
GString::~GString() {

}
//===============================================
const char* GString::c_str() const {
    return m_data.toStdString().c_str();
}
//===============================================
const QString& GString::data() const {
    return m_data;
}
//===============================================
QString& GString::data() {
    return m_data;
}
//===============================================
GString GString::extract(int _pos, const GString& _sep) {
    GString lWord = "";
    int lPos = 0;
    for(int i = 0; i < m_data.size(); i++) {
        char lChar = m_data.at(i).toLatin1();
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
int GString::count(const GString& _sep) {
    int lCount = 1;
    for(int i = 0; i < m_data.size(); i++) {
        char lChar = m_data.at(i).toLatin1();
        if(_sep.isSep(lChar)) {
            lCount++;
        }
    }
    return lCount;
}
//===============================================
bool GString::isEmpty() const {
    return m_data.isEmpty();
}
//===============================================
bool GString::isSep(char _char) const {
    for(int i = 0; i < m_data.size(); i++) {
        if(m_data[i] == _char) return true;
    }
    return false;
}
//===============================================
int GString::size() const {
    return m_data.size();
}
//===============================================
bool GString::startBy(const GString& _data) const {
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
int GString::sepSize(int _pos, const GString& _sep) const {
    int lSize = 0;
    int lCount = 0;
    for(int i = 0; i < m_data.size(); i++) {
        char lChar = m_data.at(i).toLatin1();
        lSize++;
        if(_sep.isSep(lChar)) {
            if(lCount == _pos) break;
            lCount++;
        }
    }
    return lSize;
}
//===============================================
GString GString::trim(const GString& _sep) {
    int lStartPos = 0;
    int lEndPos = m_data.size() - 1;
    GString lData = "";
    for(int i = 0; i < m_data.size(); i++) {
        char lChar = m_data.at(i).toLatin1();
        if(!_sep.isSep(lChar)) break;
        lStartPos++;
    }
    for(int i = m_data.size() - 1; i >= 0 ; i--) {
        char lChar = m_data.at(i).toLatin1();
        if(!_sep.isSep(lChar)) break;
        lEndPos--;
    }
    for(int i = lStartPos; i <= lEndPos; i++) {
        char lChar = m_data.at(i).toLatin1();
        lData += lChar;
    }
    return lData;
}
//===============================================
int GString::toInt() const {
    int lData = m_data.toInt();
    return lData;
}
//===============================================
GString& GString::operator=(const GString& _data) {
    m_data = _data.m_data;
    return *this;
}
//===============================================
GString& GString::operator=(const QString& _data) {
    m_data = _data;
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
    m_data = QString("%1").arg(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(const GString& _data) {
    m_data += _data.m_data;
    return *this;
}
//===============================================
GString& GString::operator+=(const QString& _data) {
    m_data += _data;
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
    m_data += QString("%1").arg(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(char _data) {
    m_data += _data;
    return *this;
}
//===============================================
bool GString::operator==(const GString& _data) {
    bool lEqual = true;
    lEqual &= (m_data == _data.m_data);
    return lEqual;
}
//===============================================
bool GString::operator==(const QString& _data) {
    bool lEqual = true;
    lEqual &= (m_data == _data);
    return lEqual;
}
//===============================================
bool GString::operator==(const std::string& _data) {
    bool lEqual = true;
    lEqual &= (m_data == _data.c_str());
    return lEqual;
}
//===============================================
bool GString::operator==(const char* _data) {
    QString lData = _data;
    bool lEqual = true;
    lEqual &= (m_data == lData);
    return lEqual;
}
//===============================================
bool GString::operator==(char _data) {
    bool lEqual = true;
    lEqual &= (m_data[0] == _data);
    return lEqual;
}
//===============================================
bool GString::operator==(int _data) {
    QString lData = QString("%1").arg(_data);
    bool lEqual = true;
    lEqual &= (m_data == lData);
    return lEqual;
}
//===============================================
bool GString::operator!=(const GString& _data) {
    bool lEqual = true;
    lEqual &= (m_data != _data.m_data);
    return lEqual;
}
//===============================================
bool GString::operator!=(const QString& _data) {
    bool lEqual = true;
    lEqual &= (m_data != _data);
    return lEqual;
}
//===============================================
bool GString::operator!=(const std::string& _data) {
    bool lEqual = true;
    lEqual &= (m_data != _data.c_str());
    return lEqual;
}
//===============================================
bool GString::operator!=(const char* _data) {
    QString lData = _data;
    bool lEqual = true;
    lEqual &= (m_data != lData);
    return lEqual;
}
//===============================================
bool GString::operator!=(char _data) {
    bool lEqual = true;
    lEqual &= (m_data.at(0).toLatin1() != _data);
    return lEqual;
}
//===============================================
bool GString::operator!=(int _data) {
    QString lData = QString("%1").arg(_data);
    bool lEqual = true;
    lEqual &= (m_data == lData);
    return lEqual;
}
//===============================================
char& GString::operator[](int _index) {
    return m_data.toUtf8().data()[_index];
}
//===============================================
const char& GString::operator[](int _index) const {
    return m_data.toUtf8().data()[_index];
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
