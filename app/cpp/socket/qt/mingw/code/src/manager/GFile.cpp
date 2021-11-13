//===============================================
#include <GFile.h>
//===============================================
GFile::GFile() {

}
//===============================================
GFile::~GFile() {

}
//===============================================
void GFile::openRead(const QString& _filename) {
    m_file.setFileName(_filename);
    m_file.open(QFile::ReadOnly | QFile::Text);
}
//===============================================
void GFile::openWrite(const QString& _filename) {
    m_file.setFileName(_filename);
    m_file.open(QFile::WriteOnly | QFile::Text);
}
//===============================================
QFile& GFile::file() {
    return m_file;
}
//===============================================
void GFile::close() {
    m_file.close();
}
//===============================================
