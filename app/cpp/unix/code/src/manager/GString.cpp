//===============================================
#include "GString.h"
#include "GLog.h"
#include "GFormat.h"
#include "GError.h"
//===============================================
GString::GString() : GObject() {
    m_data = "";
    // errors
    m_errors.reset(new GError);
}
//===============================================
GString::GString(const std::string& _data) : GObject() {
    m_data = _data;
    // errors
    m_errors.reset(new GError);
}
//===============================================
GString::GString(int _data) : GObject(){
    m_data = std::to_string(_data);
    // errors
    m_errors.reset(new GError);
}
//===============================================
GString::GString(const GString& _data) : GObject() {
    m_data = _data.m_data;
    // errors
    m_errors.reset(new GError);
}
//===============================================
GString::~GString() {

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
    catch(const std::invalid_argument& e) {
        GERROR_OBJ(eGERR, "Erreur la chaine est invalide.\n"
                "erreur.......: (%s)\n"
                "chaine.......: (%s)\n"
                "", e.what(), m_data.c_str());
        return 0;
    }
    catch(const std::out_of_range& e) {
        GERROR_OBJ(eGERR, "Erreur le nombre depasse les limites de conversion.\n"
                "erreur.......: (%s)\n"
                "", e.what());
        return 0;
    }
    return lData;
}
//===============================================
bool GString::toBool() const {
    return (toInt() == 1);
}
//===============================================
GString& GString::operator+=(const GString& _data) {
    m_data += _data.m_data;
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
