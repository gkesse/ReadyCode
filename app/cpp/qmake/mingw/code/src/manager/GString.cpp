//===============================================
#include "GString.h"
//===============================================
GString* GString::m_instance = 0;
//===============================================
GString::GString() {
    m_data = 0;
    m_size = 0;
    clear();
}
//===============================================
GString::GString(const QString& _data) {
    m_data = 0;
    m_size = 0;
    assign(_data);
}
//===============================================
GString::GString(const std::string& _data) {
    m_data = 0;
    m_size = 0;
    assign(_data);
}
//===============================================
GString::GString(const char* _data) {
    m_data = 0;
    m_size = 0;
    assign(_data);
}
//===============================================
GString::GString(char _data) {
    m_data = 0;
    m_size = 0;
    assign(_data);
}
//===============================================
GString::GString(bool _data) {
    m_data = 0;
    m_size = 0;
    assign(_data);
}
//===============================================
GString::GString(int _data) {
    m_data = 0;
    m_size = 0;
    assign(_data);
}
//===============================================
GString::GString(const std::vector<char>& _data) {
    m_data = 0;
    m_size = 0;
    assign(_data);
}
//===============================================
GString::GString(const std::vector<uchar>& _data) {
    m_data = 0;
    m_size = 0;
    assign(_data);
}
//===============================================
GString::GString(const GString& _data) {
    m_data = 0;
    m_size = 0;
    assign(_data);
}
//===============================================
GString::~GString() {
    clear();
}
//===============================================
GString* GString::Instance() {
    if(m_instance == 0) {
        m_instance = new GString;
    }
    return m_instance;
}
//===============================================
void GString::clear() {
    if(m_data) delete[] m_data;
    m_data = 0;
    m_size = 0;
}
//===============================================
bool GString::allocate(int _size) {
    clear();
    m_size = _size;
    if(!m_size) return false;
    m_data = new char[m_size + 1];
    return true;
}
//===============================================
void GString::assign(const QString& _data) {
    clear();
    m_size = (int)_data.size();
    if(m_size == 0) return;
    m_data = new char[m_size + 1];
    for(int i = 0; i < m_size; i++) {
        char lChar = (char)_data.at(i).toLatin1();
        m_data[i] = lChar;
    }
    m_data[m_size] = '\0';
}
//===============================================
void GString::assign(const std::string& _data) {
    clear();
    m_size = (int)_data.size();
    if(m_size == 0) return;
    m_data = new char[m_size + 1];
    for(int i = 0; i < m_size; i++) {
        char lChar = _data[i];
        m_data[i] = lChar;
    }
    m_data[m_size] = '\0';
}
//===============================================
void GString::assign(const char* _data) {
    clear();
    if(_data == 0) return;
    m_size = (int)strlen(_data);
    if(m_size == 0) return;
    m_data = new char[m_size + 1];
    for(int i = 0; i < m_size; i++) {
        char lChar = _data[i];
        m_data[i] = lChar;
    }
    m_data[m_size] = '\0';
}
//===============================================
void GString::assign(char _data) {
    clear();
    m_size = 1;
    m_data = new char[m_size + 1];
    m_data[0] = _data;
    m_data[m_size] = '\0';
}
//===============================================
void GString::assign(bool _data) {
    clear();
    char lData = (_data ? '1' : '0');
    m_size = 1;
    m_data = new char[m_size + 1];
    m_data[0] = lData;
    m_data[m_size] = '\0';
}
//===============================================
void GString::assign(int _data) {
    clear();
    int lDivisor = 1;
    int lBufferLength = 1;
    int lIsNegative = 0;
    int lBufferIndex = 0;

    if(_data < 0) {
        lIsNegative = 1;
        _data *= -1;
        lBufferIndex++;
    }

    while(_data / lDivisor >= 10) {
        lDivisor *= 10;
        lBufferLength++;
    }

    m_size = lBufferLength + lIsNegative;
    m_data = new char[m_size + 1];
    m_data[0] = (lIsNegative ? '-' : '\0');

    while(lBufferLength > 0) {
        m_data[lBufferIndex] = '0' + _data / lDivisor;
        _data = _data % lDivisor;
        lDivisor = lDivisor / 10;
        lBufferIndex++;
        lBufferLength--;
    }

    m_data[lBufferIndex] = '\0';
}
//===============================================
void GString::assign(const std::vector<char>& _data) {
    clear();
    m_size = (int)_data.size();
    if(m_size == 0) return;
    m_data = new char[m_size + 1];
    for(int i = 0; i < m_size; i++) {
        char lChar = _data[i];
        m_data[i] = lChar;
    }
    m_data[m_size] = '\0';
}
//===============================================
void GString::assign(const std::vector<uchar>& _data) {
    clear();
    m_size = (int)_data.size();
    if(m_size == 0) return;
    m_data = new char[m_size + 1];
    for(int i = 0; i < m_size; i++) {
        char lChar = _data[i];
        m_data[i] = lChar;
    }
    m_data[m_size] = '\0';
}
//===============================================
void GString::assign(const GString& _data) {
    clear();
    m_size = _data.m_size;
    if(m_size == 0) return;
    m_data = new char[m_size + 1];
    for(int i = 0; i < m_size; i++) {
        char lChar = _data.m_data[i];
        m_data[i] = lChar;
    }
    m_data[m_size] = '\0';
}
//===============================================
char*& GString::data() {
    return m_data;
}
//===============================================
const char* GString::data() const {
    return m_data;
}
//===============================================
const char* GString::c_str() const {
    return m_data;
}
//===============================================
GString GString::extract(int _pos, const GString& _sep) const {
    GString lWord = "";
    int lPos = 0;
    for(int i = 0; i < m_size; i++) {
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
int GString::countSep(const GString& _sep) const {
    int lCount = 1;
    for(int i = 0; i < m_size; i++) {
        char lChar = m_data[i];
        if(_sep.isSep(lChar)) {
            lCount++;
        }
    }
    return lCount;
}
//===============================================
bool GString::isEmpty() const {
    if(!m_data || !m_size) return true;
    return false;
}
//===============================================
bool GString::isSep(char _char) const {
    for(int i = 0; i < m_size; i++) {
        if(m_data[i] == _char) return true;
    }
    return false;
}
//===============================================
int GString::size() const {
    return m_size;
}
//===============================================
bool GString::startBy(const GString& _data) const {
    if((int)m_size == 0) return false;
    if(_data.size() == 0) return false;
    if((int)m_size < _data.size()) return false;
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
    for(int i = 0; i < m_size; i++) {
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
GString GString::trim(const GString& _sep) const {
    int lStartPos = 0;
    int lEndPos = m_size - 1;
    GString lData = "";
    for(int i = 0; i < m_size; i++) {
        char lChar = m_data[i];
        if(!_sep.isSep(lChar)) break;
        lStartPos++;
    }
    for(int i = (int)m_size - 1; i >= 0 ; i--) {
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
GString GString::substr(int _pos, int _size) const {
    if(!m_data || !m_size) return "";

    if(_pos < 0) {
        _pos = m_size + _pos;
    }
    if(_pos < 0) {
        _pos = 0;
    }

    if(_pos > m_size) {
        _pos = m_size;
    }

    int lLength = m_size - _pos;

    if (_size > lLength) {
        _size = lLength;
    }

    GString lData;
    if(lData.allocate(_size)) {
        memcpy(lData.m_data, m_data + _pos, _size);
        lData.m_data[_size] = '\0';
    }
    return lData;
}
//===============================================
bool GString::toBool() const {
    if(!m_data) return false;
    if(m_size == 0) return false;
    if(m_size > 1) return false;
    return (m_data[0] == '1');
}
//===============================================
int GString::toInt() const {
    int lData = 0;
    toInt(lData);
    return lData;
}
//===============================================
bool GString::toInt(int& _data, int _defaultValue) const {
    try {
        _data = std::stoi(m_data);
    }
    catch(const std::exception& e) {
        _data = _defaultValue;
        return false;
    }
    return true;
}
//===============================================
std::vector<char> GString::toVector() const {
    std::vector<char> lData(m_data, m_data + m_size);
    return lData;
}
//===============================================
GString GString::getFormat(const char* _format, ...) const {
    va_list lArgs;
    va_start (lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    if(lSize == 0) return "";
    GString lData;
    lData.allocate(lSize);
    vsnprintf(lData.m_data, lData.m_size + 1, _format, lArgs);
    va_end(lArgs);
    return lData;
}
//===============================================
GString GString::getFilename() const {
    if(isEmpty()) return "";
    int lCount = countSep("/\\");
    return extract(lCount - 1, "/\\");
}
//===============================================
void GString::print() const {
    printf("%s\n", m_data);
}
//===============================================
GString& GString::operator=(const GString& _data) {
    assign(_data);
    return *this;
}
//===============================================
GString& GString::operator=(const QString& _data) {
    assign(_data);
    return *this;
}
//===============================================
GString& GString::operator=(const std::vector<char>& _data) {
    assign(_data);
    return *this;
}
//===============================================
GString& GString::operator=(const std::vector<uchar>& _data) {
    assign(_data);
    return *this;
}
//===============================================
GString& GString::operator=(const std::string& _data) {
    assign(_data);
    return *this;
}
//===============================================
GString& GString::operator=(const char* _data) {
    assign(_data);
    return *this;
}
//===============================================
GString& GString::operator=(char _data) {
    assign(_data);
    return *this;
}
//===============================================
GString& GString::operator=(bool _data) {
    assign(_data);
    return *this;
}
//===============================================
GString& GString::operator=(int _data) {
    assign(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(const GString& _data) {
    if(!_data.m_data || !_data.m_size) return *this;
    char* lBuffer = m_data;
    int lSize = m_size + _data.m_size;
    m_data = new char[lSize + 1];
    for(int i = 0; i < m_size; i++) {
        m_data[i] = lBuffer[i];
    }
    for(int i = 0; i < _data.m_size; i++) {
        m_data[m_size + i] = _data[i];
    }
    m_size = lSize;
    m_data[m_size] = '\0';
    if(lBuffer) delete[] lBuffer;
    lBuffer = 0;
    return *this;
}
//===============================================
GString& GString::operator+=(const QString& _data) {
    *this += GString(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(const std::string& _data) {
    *this += GString(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(const char* _data) {
    *this += GString(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(int _data) {
    *this += GString(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(char _data) {
    *this += GString(_data);
    return *this;
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
bool GString::operator==(const QString& _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator==(const std::string& _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator==(const char* _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator==(char _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator==(int _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator!=(const GString& _data) const {
    return !(*this == _data);
}
//===============================================
bool GString::operator!=(const QString& _data) const {
    return !(*this == GString(_data));
}
//===============================================
bool GString::operator!=(const std::string& _data) const {
    return !(*this == GString(_data));
}
//===============================================
bool GString::operator!=(const char* _data) const {
    return !(*this == GString(_data));
}
//===============================================
bool GString::operator!=(char _data) const {
    return !(*this == GString(_data));
}
//===============================================
bool GString::operator!=(int _data) const {
    return !(*this == GString(_data));
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
