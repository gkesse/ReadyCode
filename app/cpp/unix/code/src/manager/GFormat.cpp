//===============================================
#include "GFormat.h"
//===============================================
GFormat* GFormat::m_instance = 0;
//===============================================
GFormat::GFormat() : GObject() {

}
//===============================================
GFormat::~GFormat() {

}
//===============================================
GFormat* GFormat::Instance() {
    if(m_instance == 0) {
        m_instance = new GFormat;
    }
    return m_instance;
}
//===============================================
std::string GFormat::getFormat(const char* _format, ...) {
    va_list lArgs;
    va_start (lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    std::vector<char> lData(lSize + 1);
    vsnprintf(lData.data(), lData.size(), _format, lArgs);
    va_end(lArgs);
    return lData.data();
}
//===============================================
std::string GFormat::getFormatInt(int _data, int _size) {
    std::vector<char> lBuffer(_size + 1);
    snprintf(lBuffer.data(), lBuffer.size(), "%-*d", _size, _data);
    std::string lData = lBuffer.data();
    return lData;
}
//===============================================
