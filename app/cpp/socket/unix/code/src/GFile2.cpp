//===============================================
#include "GFile2.h"
//===============================================
GFile2::GFile2() {
	m_filename = "";
	m_fileId = 0;
}
//===============================================
GFile2::~GFile2() {

}
//===============================================
void GFile2::setFilename(const std::string& filename) {
    m_filename = filename;
}
//===============================================
void GFile2::openFile() {
	m_fileId = open(m_filename.c_str(), O_WRONLY | O_CREAT | O_APPEND);
}
//===============================================
void GFile2::writeData(const char* data, int size) {
	write(m_fileId, data, size);
}
//===============================================
void GFile2::writeData(const GString& data) {
	writeData(data.c_str(), data.getSize());
}
//===============================================
