//===============================================
#include "GFile.h"
//===============================================
GFile::GFile() : GObject() {
    m_filename = "";
}
//===============================================
GFile::GFile(const std::string& _filename) : GObject() {
    m_filename = _filename;
}
//===============================================
GFile::~GFile() {

}
//===============================================
std::string GFile::getData() const {
    std::ifstream lFile(m_filename);
    std::stringstream lBuffer;
    lBuffer << lFile.rdbuf();
    return lBuffer.str();
}
//===============================================
