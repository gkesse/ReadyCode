//===============================================
#include "GBase64.h"
//===============================================
GBase64::GBase64() : GObject() {
    m_data = "";
}
//===============================================
GBase64::GBase64(const GString& _data) : GObject() {
    m_data = _data;
}
//===============================================
GBase64::~GBase64() {

}
//===============================================
GString GBase64::encodeData() const {
    if(m_data == "") return "";
    GString lData = base64::to_base64(m_data);
    return lData;
}
//===============================================
GString GBase64::decodeData() const {
    if(m_data == "") return "";
    GString lData = base64::from_base64(m_data);
    return lData;
}
//===============================================
