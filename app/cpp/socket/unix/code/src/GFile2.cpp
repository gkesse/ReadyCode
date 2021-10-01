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
void GFile2::openFile2() {
    m_fileId = open(m_filename.c_str(), O_RDONLY);
}
//===============================================
int GFile2::writeData(const char* data, int size) {
    return write(m_fileId, data, size);
}
//===============================================
int GFile2::writeData(const GString& data) {
    return writeData(data.c_str(), data.size());
}
//===============================================
int GFile2::readData(char* data, int size) {
    return read(m_fileId, data, size);
}
//===============================================
int GFile2::readAll(GString& data) {
	const int BUFFER_SIZE = 1024;
	char lBuffer[BUFFER_SIZE + 1];
	int lSize = 0;
	data.clear();
    while(1) {
        int lBytes = readData(lBuffer, BUFFER_SIZE);
        if(lBytes <= 0) {break;}
        data.addData(lBuffer, lBytes);
        lSize += lBytes;
    }
    return lSize;
}
//===============================================
void GFile2::closeFile() {
    close(m_fileId);
}
//===============================================
