//===============================================
#include "GString.h"
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
bool GString::toInt(int& _number) const {
    if(m_data == "") return false;
    try {
        _number = std::stoi(m_data);
    }
    catch(const std::invalid_argument& e) {
        GOBJ_ERR_ADD("La chaine est invalide.\n"
                "- erreur......: %s", e.what());
        return false;
    }
    catch(const std::out_of_range& e) {
        GOBJ_ERR_ADD("Le nombre depasse les limites de conversion.\n"
                "- erreur......: %s", e.what());
        return false;
    }
    return 0;
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
