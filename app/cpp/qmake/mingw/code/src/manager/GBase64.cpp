//===============================================
#include "GBase64.h"
//===============================================
GBase64::GBase64()
: GObject() {

}
//===============================================
GBase64::GBase64(const GString& _data)
: GObject() {
    m_data = _data;
}
//===============================================
GBase64::~GBase64() {

}
//===============================================
GString GBase64::encodeData() const {
    if(m_data.isEmpty()) return "";
    GString lData = Base64::encode((uchar*)m_data.data(), m_data.size());
    return lData;
}
//===============================================
GString GBase64::decodeData() const {
    if(m_data == "") return "";
    GString lData = Base64::decode(m_data.c_str());
    return lData;
}
//===============================================
