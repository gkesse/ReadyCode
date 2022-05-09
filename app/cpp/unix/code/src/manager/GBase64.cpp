//===============================================
#include "GBase64.h"
//===============================================
GBase64::GBase64() : GObject() {
    m_data = "";
}
//===============================================
GBase64::GBase64(const std::string& _data) : GObject() {
    m_data = _data;
}
//===============================================
GBase64::~GBase64() {

}
//===============================================
std::string GBase64::encodeData() const {
    if(m_data == "") return "";
    std::string lData = base64::to_base64(m_data);
    return lData;
}
//===============================================
std::string GBase64::decodeData() const {
    if(m_data == "") return "";
    std::string lData = base64::from_base64(m_data);
    return lData;
}
//===============================================
