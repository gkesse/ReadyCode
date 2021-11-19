//===============================================
#include "GLog.h"
//===============================================
GLog* GLog::m_instance = 0;
//===============================================
GLog::GLog() {

}
//===============================================
GLog::~GLog() {

}
//===============================================
GLog* GLog::Instance() {
	if(m_instance == 0) {
		m_instance = new GLog;
	}
	return m_instance;
}
//===============================================
void GLog::log(const char* _level, const char* _file, int _line, const char* _func) {
	printf("[ %s ] [ %s ] [ %d ] [ %s() ]\n", _level, _file, _line, _func);
}
//===============================================
void GLog::log(const char* _level, const char* _file, int _line, const char* _func, const char* _format, ...) {
	char lBuffer[BUFFER_SIZE + 1];
	va_list lArgs;
	va_start(lArgs, _format);
	vsprintf(lBuffer, _format, lArgs);
	va_end(lArgs);
	printf("[ %s ] [ %s ] [ %d ] [ %s() ] : %s\n", _level, _file, _line, _func, lBuffer);
}
//===============================================
