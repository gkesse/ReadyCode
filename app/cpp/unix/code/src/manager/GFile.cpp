//===============================================
#include "GFile.h"
#include "GShell.h"
#include "GEnv.h"
#include "GDate.h"
//===============================================
GFile::GFile() : GObject() {
    m_filename = "";
    m_openType = "";
}
//===============================================
GFile::GFile(const GString& _filename) : GObject() {
    m_filename = _filename;
    m_openType = "";
}
//===============================================
GFile::GFile(const GString& _filename, const GString& _openType) : GObject() {
    m_filename = _filename;
    m_openType = _openType;
}
//===============================================
GFile::~GFile() {

}
//===============================================
bool GFile::existFile() const {
    if(m_filename == "") return false;
    struct stat lBuffer;
    return (stat(m_filename.c_str(), &lBuffer) == 0);
}
//===============================================
GString GFile::getContent() const {
    if(m_filename == "") return "";
    if(!existFile()) return "";
    std::ifstream lFile(m_filename.c_str());
    std::stringstream lBuffer;
    lBuffer << lFile.rdbuf();
    return lBuffer.str();
}
//===============================================
void GFile::setContent(const GString& _data) {
    if(m_filename == "") return;
    std::ofstream lFile(m_filename.c_str());
    lFile << _data;
}
//===============================================
GString GFile::getAppendType() const {
    return "a+";
}
//===============================================
GString GFile::getLogFullname() const {
    return getLogFullname(GEnv().isTestEnv());
}
//===============================================
GString GFile::getLogFullname(bool _isTestEnv) const {
    GString lFilename = getDateFullname("log_prod_", ".txt");
    if(_isTestEnv) lFilename = getDateFullname("log_test_", ".txt");
    return lFilename;
}
//===============================================
GString GFile::getScriptInFilename() const {
    GString lFilename = getDateFilename("script_", "_in.txt");
    return lFilename;
}
//===============================================
GString GFile::getScriptOutFilename() const {
    GString lFilename = getDateFilename("script_", "_out.txt");
    return lFilename;
}
//===============================================
GString GFile::getDateFullname(const GString& _key, const GString& _ext) const {
    GString lTmpDir = GEnv().getTmpDir();
    GString lFilename = getDateFilename(_key, _ext);
    lFilename = getFullname(lTmpDir, lFilename);
    return lFilename;
}
//===============================================
GString GFile::getDateFilename(const GString& _key, const GString& _ext) const {
    GString lDate = GDate().getDate(GDate().getDateFileFormat());
    return getFilename(_key, lDate, _ext);
}
//===============================================
GString GFile::getFilename(const GString& _key, const GString& _date, const GString& _ext) const {
    GString lFilename = GFORMAT("%s%s%s", _key.c_str(), _date.c_str(), _ext.c_str());
    return lFilename;
}
//===============================================
GString GFile::getFullname(const GString& _path, const GString& _filename) const {
    GShell().createDir(_path);
    GString lFilename = GFORMAT("%s/%s", _path.c_str(), _filename.c_str());
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
    FILE* lFile = fopen(m_filename.c_str(), m_openType.c_str());
    return lFile;
}
//===============================================
FILE* GFile::openFile(const GString& _openType) {
    if(m_filename == "") return 0;
    FILE* lFile = fopen(m_filename.c_str(), _openType.c_str());
    return lFile;
}
//===============================================
FILE* GFile::openFile(const GString& _filename, const GString& _openType) {
    FILE* lFile = fopen(_filename.c_str(), _openType.c_str());
    m_filename = _filename;
    m_openType = _openType;
    return lFile;
}
//===============================================
void GFile::closeFile(FILE* _file) {
    fclose(_file);
}
//===============================================
