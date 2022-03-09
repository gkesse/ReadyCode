//===============================================
#include "GFormat.h"
//===============================================
GFormat* GFormat::m_instance = 0;
//===============================================
GFormat::GFormat() {

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
std::string GFormat::sformat(const char* _format, ...) {
	va_list lArgs;
	va_start (lArgs, _format);
	vsprintf(m_buffer, _format, lArgs);
	va_end (lArgs);
	return m_buffer;
}
//===============================================
