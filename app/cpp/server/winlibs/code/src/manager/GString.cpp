//===============================================
#include "GString.h"
//===============================================
GString* GString::m_instance = 0;
//===============================================
GString::GString() {
    m_data = 0;
    m_size = 0;
}
//===============================================
GString::GString(const char* _data, int _size) {
    create(_data, _size);
}
//===============================================
GString::GString(const char* _data) {
    create(_data, strlen(_data));
}
//===============================================
GString::GString(const std::string& _data) {
    create(_data.data(), _data.size());
}
//===============================================
GString::GString(const std::vector<char>& _data) {
    create(_data.data(), _data.size());
}
//===============================================
GString::GString(const GString& _data) {
    create(_data.m_data, _data.m_size);
}
//===============================================
GString::~GString() {
    clear();
}
//===============================================
void GString::clear() {
    delete[] m_data;
    m_data = 0;
    m_size = 0;
}
//===============================================
GString* GString::Instance() {
    if(m_instance == 0) {
        m_instance = new GString;
    }
    return m_instance;
}
//===============================================
void GString::create(int _size) {
    m_size = _size;
    m_data = new char[m_size + 1];
    m_data[m_size] = '\0';
}
//===============================================
void GString::create(const char* _data, int _size) {
    create(_size);
    memcpy(m_data, _data, m_size);
}
//===============================================
bool GString::isEmpty() const {
    if(!m_data || !m_size) return true;
    return false;
}
//===============================================
const char* GString::c_str() const {
    return m_data;
}
//===============================================
int GString::size() const {
    return m_size;
}
//===============================================
GString GString::getFormat(const char* _format, ...) const {
    va_list lArgs;
    va_start(lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    GString lData;
    lData.create(lSize);
    vsnprintf(lData.m_data, lData.m_size + 1, _format, lArgs);
    va_end(lArgs);
    return lData;
}
//===============================================
std::vector<GString> GString::split(const GString& _sep) const {
    std::vector<GString> lMap;
    char* lToken = strtok(m_data, _sep.c_str());

    while(lToken) {
        GString lValue = lToken;
        lMap.push_back(lToken);
        lToken = strtok(0, _sep.c_str());
    }

    return lMap;
}
//===============================================
bool GString::startsWith(const GString& _data) const {
    if(isEmpty()) return false;
    if(isEmpty()) return false;
    if(m_size < _data.m_size) return false;
    std::string lDataIn(m_data);
    std::string lDataOut(_data.m_data);
    return (lDataIn.compare(0, _data.m_size, lDataOut) == 0);
}
//===============================================
bool GString::endsWith(const GString& _data) const {
    if(isEmpty()) return false;
    if(isEmpty()) return false;
    if(m_size < _data.m_size) return false;
    std::string lDataIn(m_data);
    std::string lDataOut(_data.m_data);
    return (lDataIn.compare(m_size - _data.m_size, _data.m_size, lDataOut) == 0);
}
//===============================================
GString GString::toUtf8() const {
    if(isEmpty()) return "";
    char* lBufIn = m_data;
    size_t lSizeIn = strlen(lBufIn);
    size_t lSizeOut = sizeof(wchar_t) * lSizeIn * 4;
    char* lBufOut = new char[lSizeOut];
    memset(lBufOut, '\0', lSizeOut);
    iconv_t lIconv = iconv_open("WINDOWS-1252", "UTF-8");
    GString lData;
    if(lIconv != (iconv_t)-1) {
        char* lPtrIn = lBufIn;
        char* lPtrOut = lBufOut;
        size_t lBufOutLeft = lSizeOut;
        size_t lResult = iconv(lIconv, &lPtrIn, &lSizeIn, &lPtrOut, &lBufOutLeft);
        if(lResult != -1) {
            int lSize = lSizeOut - lBufOutLeft;
            lData.create(lBufOut, lSize);
        }
        iconv_close(lIconv);
    }
    //delete[] lBufOut;
    return lData;
}
//===============================================
GString GString::toBase64() const {
    if(isEmpty()) return "";
    char* lBuffer = b64_encode((const unsigned char*)m_data, m_size);
    GString lData = lBuffer;
    free(lBuffer);
    return lData;
}
//===============================================
GString GString::fromBase64() const {
    if(isEmpty()) return "";
    char* lBuffer = (char*)b64_decode(m_data, m_size);
    GString lData = lBuffer;
    free(lBuffer);
    return lData;
}
//===============================================
void GString::print() const {
    printf("%s\n", m_data);
}
//===============================================
GString& GString::operator=(const char* _data) {
    clear();
    create(_data, strlen(_data));
    return *this;
}
//===============================================
GString& GString::operator=(const std::string& _data) {
    clear();
    create(_data.data(), _data.size());
    return *this;
}
//===============================================
GString& GString::operator=(const std::vector<char>& _data) {
    clear();
    create(_data.data(), _data.size());
    return *this;
}
//===============================================
GString& GString::operator=(const GString& _data) {
    clear();
    create(_data.m_data, _data.m_size);
    return *this;
}
//===============================================
bool GString::operator==(const char* _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator==(const std::string& _data) const {
    return (*this == GString(_data));
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
bool GString::operator!=(const char* _data) const {
    return !(*this == GString(_data));
}
//===============================================
bool GString::operator!=(const std::string& _data) const {
    return !(*this == GString(_data));
}
//===============================================
bool GString::operator!=(const GString& _data) const {
    return !(*this == _data);
}
//===============================================
bool GString::operator<(const GString& _data) const {
    int lCompare = strcmp(m_data, _data.m_data);
    if(lCompare < 0) return true;
    return false;
}
//===============================================
GString& GString::operator+=(const char* _data) {
    *this += GString(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(const std::string& _data) {
    *this += GString(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(const GString& _data) {
    char* lBuffer = m_data;
    int lSizeA = m_size;
    int lSizeB = _data.m_size;
    int lSizeT = lSizeA + lSizeB;
    create(lSizeT);
    memcpy(&m_data[0], lBuffer, lSizeA);
    memcpy(&m_data[lSizeA], _data.m_data, lSizeB);
    delete[] lBuffer;
    return *this;
}
//===============================================
char& GString::operator[](int i) {
    return m_data[i];
}
//===============================================
const char& GString::operator[](int i) const {
    return m_data[i];
}
//===============================================
