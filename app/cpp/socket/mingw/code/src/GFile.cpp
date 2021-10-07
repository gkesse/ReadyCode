//===============================================
#include "GFile.h"
//===============================================
GFile::GFile() {
    m_pFile = 0;
}
//===============================================
GFile::~GFile() {
    if(m_pFile) {fclose(m_pFile);}
}
//===============================================
void GFile::filename(const std::string& _filename) {
    m_filename = _filename;
}
//===============================================
int GFile::size() const {
    std::fstream lFile;
    lFile.open(m_filename, std::ios::in | std::ios::binary);

    lFile.seekg(0, std::ios::end);
    int lSize = lFile.tellg();
    lFile.close();
    return lSize;
}
//===============================================
void GFile::open(){
    m_pFile = fopen(m_filename.c_str(), "r");
}
//===============================================
void GFile::close(){
    fclose(m_pFile);
}
//===============================================
int GFile::read(const char* _format, ...) {
    va_list lArgs;
    va_start(lArgs, _format);
    int lAnswer = vfscanf(m_pFile, _format, lArgs);
    va_end(lArgs);
    return lAnswer;
}
//===============================================
int GFile::read(float& _data) {
    float lData;
    int lAnswer = fscanf(m_pFile, "%f\n", &lData);
    _data = lData;
    return lAnswer;
}
//===============================================
std::string GFile::read() {
    std::ifstream lFile(m_filename, std::ios::in);
    std::string lData, lLine;
    while(std::getline(lFile, lLine)) {
        lData += "\n" + lLine;
    }
    lFile.close();
    return lData;
}
//===============================================
