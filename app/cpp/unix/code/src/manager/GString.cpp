//===============================================
#include "GString.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GString::GString()
: GObject() {
    m_data = "";
}
//===============================================
GString::GString(const std::string& _data)
: GObject() {
    m_data = _data;
}
//===============================================
GString::GString(const char* _data)
: GObject() {
    m_data = _data;
}
//===============================================
GString::GString(int _data)
: GObject(){
    m_data = std::to_string(_data);
}
//===============================================
GString::GString(const GString& _data)
: GObject() {
    m_data = _data.m_data;
}
//===============================================
GString::~GString() {

}
//===============================================
std::string GString::data() const {
    return m_data;
}
//===============================================
const char* GString::c_str() const {
    return m_data.data();
}
//===============================================
std::vector<std::string> GString::splitData(char _sep) const {
    std::vector<std::string> lDataOut;
    std::istringstream lStream(m_data);
    std::string lData;
    while (std::getline(lStream, lData, _sep)) {
        lDataOut.push_back(lData);
    }
    return lDataOut;
}
//===============================================
std::string GString::trimData() const {
    std::string lData = m_data;
    lData.erase(lData.find_last_not_of(' ') + 1);
    lData.erase(0, lData.find_first_not_of(' '));
    return lData;
}
//===============================================
int GString::toInt() const {
    std::string lDataTrim = trimData();
    int lData = 0;
    if(lDataTrim == "") return 0;
    try {
        lData = std::stoi(lDataTrim);
    }
    catch(const std::invalid_argument& e) {GERROR_ADD(eGERR, "Erreur la chaine est invalide."); lData = 0;}
    catch(const std::out_of_range& e) {GERROR_ADD(eGERR, "Erreur le nombre depasse les limites de conversion."); lData = 0;}
    return lData;
}
//===============================================
bool GString::toBool() const {
    return (toInt() != 0);
}
//===============================================
GString& GString::operator=(const GString& _data) {
    m_data = _data.m_data;
    return *this;
}
//===============================================
GString& GString::operator=(const std::string& _data) {
    m_data = _data;
    return *this;
}
//===============================================
GString& GString::operator=(const char* _data) {
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
GString& GString::operator+=(const std::string& _data) {
    m_data += _data;
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
