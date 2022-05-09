//===============================================
#include "GFile.h"
#include "GShell.h"
#include "GEnv.h"
#include "GDate.h"
//===============================================
GFile::GFile(QObject* _parent) : GObject(_parent) {
    m_filename = "";
    m_openType = "";
}
//===============================================
GFile::GFile(const QString& _filename, QObject* _parent) : GObject(_parent) {
    m_filename = _filename;
    m_openType = "";
}
//===============================================
GFile::GFile(const QString& _filename, const QString& _openType, QObject* _parent) : GObject(_parent) {
    m_filename = _filename;
    m_openType = _openType;
}
//===============================================
GFile::~GFile() {

}
//===============================================
bool GFile::existFile() const {
    if(m_filename == "") return false;
    return QFileInfo::exists(m_filename);
}
//===============================================
QString GFile::getContent() const {
    if(m_filename == "") return "";
    if(!existFile()) return "";
    std::ifstream lFile(m_filename.toStdString());
    std::stringstream lBuffer;
    lBuffer << lFile.rdbuf();
    return lBuffer.str().c_str();
}
//===============================================
void GFile::setContent(const QString& _data) {
    if(m_filename == "") return;
    std::ofstream lFile(m_filename.toStdString());
    lFile << _data.toStdString();
}
//===============================================
QString GFile::getAppendType() const {
    return "a+";
}
//===============================================
QString GFile::getLogFullname() const {
    return getLogFullname(GEnv().isTestEnv());
}
//===============================================
QString GFile::getLogFullname(bool _isTestEnv) const {
    QString lFilename = getDateFullname("log_prod_", ".txt");
    if(_isTestEnv) lFilename = getDateFullname("log_test_", ".txt");
    return lFilename;
}
//===============================================
QString GFile::getScriptInFilename() const {
    QString lFilename = getDateFilename("script_", "_in.txt");
    return lFilename;
}
//===============================================
QString GFile::getScriptOutFilename() const {
    QString lFilename = getDateFilename("script_", "_out.txt");
    return lFilename;
}
//===============================================
QString GFile::getDateFullname(const QString& _key, const QString& _ext) const {
    QString lTmpDir = GEnv().getTmpDir();
    QString lFilename = getDateFilename(_key, _ext);
    lFilename = getFullname(lTmpDir, lFilename);
    return lFilename;
}
//===============================================
QString GFile::getDateFilename(const QString& _key, const QString& _ext) const {
    QString lDate = GDate().getDate(GDate().getDateFileFormat());
    return getFilename(_key, lDate, _ext);
}
//===============================================
QString GFile::getFilename(const QString& _key, const QString& _date, const QString& _ext) const {
    QString lFilename = QString("%1%2%3").arg(_key).arg(_date).arg(_ext);
    return lFilename;
}
//===============================================
QString GFile::getFullname(const QString& _path, const QString& _filename) const {
    GShell().createDir(_path);
    QString lFilename = QString("%1/%2").arg(_path).arg(_filename);
    return lFilename;
}
//===============================================
FILE* GFile::openLogFile() {
    FILE* lFile = openFile(getLogFullname(), getAppendType());
    return lFile;
}
//===============================================
FILE* GFile::openFile() {
    if(m_filename == "") return 0;
    if(m_openType == "") return 0;
    FILE* lFile = fopen(m_filename.toStdString().c_str(), m_openType.toStdString().c_str());
    return lFile;
}
//===============================================
FILE* GFile::openFile(const QString& _openType) {
    if(m_filename == "") return 0;
    FILE* lFile = fopen(m_filename.toStdString().c_str(), _openType.toStdString().c_str());
    return lFile;
}
//===============================================
FILE* GFile::openFile(const QString& _filename, const QString& _openType) {
    FILE* lFile = fopen(_filename.toStdString().c_str(), _openType.toStdString().c_str());
    m_filename = _filename;
    m_openType = _openType;
    return lFile;
}
//===============================================
void GFile::closeFile(FILE* _file) {
    fclose(_file);
}
//===============================================
