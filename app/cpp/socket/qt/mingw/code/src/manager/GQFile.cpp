//===============================================
#include "GQFile.h"
//===============================================
GQFile::GQFile() {

}
//===============================================
GQFile::~GQFile() {

}
//===============================================
void GQFile::openRead(const QString& _filename) {
	m_file.setFileName(_filename);
	m_file.open(QFile::ReadOnly | QFile::Text);
}
//===============================================
void GQFile::openWrite(const QString& _filename) {
	m_file.setFileName(_filename);
	m_file.open(QFile::WriteOnly | QFile::Text);
}
//===============================================
QFile GQFile::file() {
	return m_file;
}
//===============================================
void GQFile::close() {
	m_file.close();
}
//===============================================
