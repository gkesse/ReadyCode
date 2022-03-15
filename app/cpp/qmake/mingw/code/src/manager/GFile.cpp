//===============================================
#include "GFile.h"
//===============================================
GFile::GFile(QObject* _parent) : GObject(_parent) {
    m_filename = "";
}
//===============================================
GFile::GFile(const QString& _filename) : GObject() {
    m_filename = _filename;
}
//===============================================
GFile::~GFile() {

}
//===============================================
QString GFile::getData() const {
    std::ifstream lFile(m_filename.toStdString());
    std::stringstream lBuffer;
    lBuffer << lFile.rdbuf();
    return lBuffer.str().c_str();
}
//===============================================
