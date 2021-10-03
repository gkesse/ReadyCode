//===============================================
#include "GFile.h"
//===============================================
GFile::GFile() {

}
//===============================================
GFile::~GFile() {

}
//===============================================
void GFile::setFilename(const std::string& filename) {
    m_filename = filename;
}
//===============================================
int GFile::getSize() const {
    std::fstream lFile;
    lFile.open(m_filename, std::ios::in | std::ios::binary);

    lFile.seekg(0, std::ios::end);
    int lSize = lFile.tellg();
    lFile.close();
    return lSize;
}
//===============================================
