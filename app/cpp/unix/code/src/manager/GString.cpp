//===============================================
#include "GString.h"
#include "GBase64.h"
//===============================================
GString* GString::m_instance = 0;
//===============================================
GString::GString() {
    m_size = 0;
    m_data = 0;
    m_pos = 0;
}
//===============================================
GString::GString(const std::string& _data) {
    create(_data.c_str(), _data.size());
}
//===============================================
GString::GString(const char* _data) {
    if(!_data) return;
    int lSize = strlen(_data);
    create(_data, lSize);
}
//===============================================
GString::GString(char* _data, int _size) {
    create(_data, _size);
}
//===============================================
GString::GString(char _data) {
    create(&_data, 1);
}
//===============================================
GString::GString(bool _data) {
    char lChar = (_data ? '1' : '0');
    create(&lChar, 1);
}
//===============================================
GString::GString(int _data) {
    int lSize = snprintf(0, 0, "%d", _data);
    if(!create(lSize)) return;
    snprintf(m_data, m_size + 1, "%d", _data);
}
//===============================================
GString::GString(const std::vector<char>& _data) {
    create(_data.data(), _data.size());
}
//===============================================
GString::GString(const std::vector<uchar>& _data) {
    create((char*)_data.data(), _data.size());
}
//===============================================
GString::GString(const GString& _data) {
    create(_data.m_data, _data.m_size, _data.m_pos);
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
bool GString::create(int _size, int _pos) {
    if(_size < 0) return false;
    m_size = _size;
    m_pos = _pos;
    m_data = new char[m_size + 1];
    m_data[m_size] = '\0';
    return true;
}
//===============================================
bool GString::create(const char* _data, int _size, int _pos) {
    if(!_data) return false;
    if(!create(_size, _pos)) return false;
    memcpy(m_data, _data, m_size);
    return true;
}
//===============================================
void GString::clear() {
    if(m_data) {
        delete[] m_data;
        m_data = 0;
        m_size = 0;
        m_pos = 0;
    }
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
    if(isEmpty()) return "";
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
GString GString::extract(int _pos, const GString& _sep) {
    GString lWord;
    int lPos = 0;
    for(int i = 0; i < m_size; i++) {
        char lChar = m_data[i];
        m_pos = i;
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
GString GString::end() const {
    GString lWord;
    for(int i = m_pos; i < m_size; i++) {
        char lChar = m_data[i];
        lWord += lChar;
    }
    return lWord;
}
//===============================================
std::vector<GString> GString::split(const GString& _sep) const {
    std::vector<GString> lMap;
    int lCount = countSep(_sep);
    for(int i = 0; i < lCount; i++) {
        GString lData = extract(i, _sep);
        lMap.push_back(lData);
    }
    return lMap;
}
//===============================================
void GString::move(int _pos) {
    m_pos += _pos;
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
int GString::indexOf(const GString& _data, int _pos) const {
    std::string lData = c_str();
    std::string::size_type lIndex = lData.find(_data.c_str(), _pos);
    return lIndex;
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
    if(m_size == 0) return false;
    if(_data.size() == 0) return false;
    if(m_size < _data.size()) return false;
    for(int i = 0; i < _data.size(); i++) {
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
    if(isEmpty()) return "";
    std::string lData = c_str();
    return lData.substr (_pos, _size);
}
//===============================================
bool GString::toBool() const {
    if(isEmpty()) return false;
    if(m_size > 1) return false;
    return (m_data[0] == '1');
}
//===============================================
char GString::toChar() const {
    if(isEmpty()) return 0;
    return m_data[0];
}
//===============================================
int GString::toInt() const {
    int lData = 0;
    toInt(lData);
    return lData;
}
//===============================================
bool GString::toInt(int& _data, int _defaultValue) const {
    if(isEmpty()) return _defaultValue;
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
GString GString::toBase64() const {
    GString lData = GBase64(*this).encodeData();
    return lData;
}
//===============================================
GString GString::fromBase64() const {
    GString lData = GBase64(*this).decodeData();
    return lData;
}
//===============================================
std::vector<char> GString::toVector() const {
    if(isEmpty()) return std::vector<char>();
    std::vector<char> lData(m_data, m_data + m_size);
    return lData;
}
//===============================================
GString GString::getFormat(const char* _format, ...) const {
    va_list lArgs;
    va_start (lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    GString lData;
    lData.create(lSize);
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
GString GString::toLower() const {
    GString lData = *this;
    for(int i = 0; i < lData.size(); i++) {
        char lChar = lData[i];
        lData[i] = std::tolower(lChar);
    }
    return lData;
}
//===============================================
GString GString::toUpper() const {
    GString lData = *this;
    for(int i = 0; i < lData.size(); i++) {
        char lChar = lData[i];
        lData[i] = std::toupper(lChar);
    }
    return lData;
}
//===============================================
void GString::print() const {
    printf("[%d]\n%s\n", m_size, m_data);
}
//===============================================
GString& GString::operator=(const GString& _data) {
    clear();
    create(_data.m_data, _data.m_size, _data.m_pos);
    return *this;
}
//===============================================
GString& GString::operator=(const std::vector<char>& _data) {
    clear();
    create(_data.data(), _data.size());
    return *this;
}
//===============================================
GString& GString::operator=(const std::vector<uchar>& _data) {
    clear();
    create((char*)_data.data(), _data.size());
    return *this;
}
//===============================================
GString& GString::operator=(const std::string& _data) {
    clear();
    create(_data.data(), _data.size());
    return *this;
}
//===============================================
GString& GString::operator=(const char* _data) {
    clear();
    if(!_data) return *this;;
    int lSize = (int)strlen(_data);
    create(_data, lSize);
    return *this;
}
//===============================================
GString& GString::operator=(char _data) {
    clear();
    create(&_data, 1);
    return *this;
}
//===============================================
GString& GString::operator=(bool _data) {
    clear();
    char lChar = (_data ? '1' : '0');
    create(&lChar, 1);
    return *this;
}
//===============================================
GString& GString::operator=(int _data) {
    clear();
    int lSize = snprintf(0, 0, "%d", _data);
    create(lSize);
    snprintf(m_data, m_size + 1, "%d", _data);
    return *this;
}
//===============================================
GString& GString::operator+=(const GString& _data) {
    if(_data.isEmpty()) return *this;
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
bool GString::operator<(const GString& _data) const {
    if(isEmpty() && _data.isEmpty()) return false;
    if(isEmpty()) return true;
    if(_data.isEmpty()) return false;
    int lCompare = strcmp(m_data, _data.m_data);
    if(lCompare < 0) return true;
    return false;
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
