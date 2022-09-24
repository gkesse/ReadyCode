//===============================================
#include "GFile2.h"
#include "GShell2.h"
#include "GEnv.h"
#include "GDate.h"
//===============================================
GFile2::GFile2()
: GObject2() {
    m_filename = "";
    m_openType = "";
}
//===============================================
GFile2::GFile2(const GString2& _filename)
: GObject2() {
    m_filename = _filename;
    m_openType = "";
}
//===============================================
GFile2::GFile2(const GString2& _filename, const GString2& _openType)
: GObject2() {
    m_filename = _filename;
    m_openType = _openType;
}
//===============================================
GFile2::~GFile2() {

}
//===============================================
bool GFile2::existFile() const {
    if(m_filename == "") return false;
    struct stat lBuffer;
    return (stat(m_filename.c_str(), &lBuffer) == 0);
}
//===============================================
GString2 GFile2::getContent() const {
    if(m_filename == "") return "";
    if(!existFile()) return "";
    std::ifstream lFile(m_filename);
    std::stringstream lBuffer;
    lBuffer << lFile.rdbuf();
    return lBuffer.str();
}
//===============================================
void GFile2::setContent(const GString2& _data) {
    if(m_filename == "") return;
    std::ofstream lFile(m_filename);
    lFile << _data;
}
//===============================================
GString2 GFile2::getAppendType() const {
    return "a+";
}
//===============================================
GString2 GFile2::getLogFullname() const {
    return getLogFullname(GEnv().isTestEnv());
}
//===============================================
GString2 GFile2::getLogFullname(bool _isTestEnv) const {
    GString2 lFilename = getDateFullname("log_prod_", ".txt");
    if(_isTestEnv) lFilename = getDateFullname("log_test_", ".txt");
    return lFilename;
}
//===============================================
GString2 GFile2::getScriptInFilename() const {
    GString2 lFilename = getDateFilename("script_", "_in.txt");
    return lFilename;
}
//===============================================
GString2 GFile2::getScriptOutFilename() const {
    GString2 lFilename = getDateFilename("script_", "_out.txt");
    return lFilename;
}
//===============================================
GString2 GFile2::getDateFullname(const GString2& _key, const GString2& _ext) const {
    GString2 lTmpDir = GEnv().getTmpDir();
    GString2 lFilename = getDateFilename(_key, _ext);
    lFilename = getFullname(lTmpDir, lFilename);
    return lFilename;
}
//===============================================
GString2 GFile2::getDateFilename(const GString2& _key, const GString2& _ext) const {
    GString2 lDate = GDate().getDate(GDate().getDateFileFormat());
    return getFilename(_key, lDate, _ext);
}
//===============================================
GString2 GFile2::getFilename(const GString2& _key, const GString2& _date, const GString2& _ext) const {
    GString2 lFilename = sformat("%s%s%s", _key.c_str(), _date.c_str(), _ext.c_str());
    return lFilename;
}
//===============================================
GString2 GFile2::getFullname(const GString2& _path, const GString2& _filename) const {
    GShell2().createDir(_path);
    GString2 lFilename = sformat("%s/%s", _path.c_str(), _filename.c_str());
    return lFilename;
}
//===============================================
FILE* GFile2::openLogFile() {
    FILE* lFile = openFile(getLogFullname(), getAppendType());
    return lFile;
}
//===============================================
FILE* GFile2::openFile() {
    if(m_filename == "") return 0;
    if(m_openType == "") return 0;
    FILE* lFile = fopen(m_filename.c_str(), m_openType.c_str());
    return lFile;
}
//===============================================
FILE* GFile2::openFile(const GString2& _openType) {
    if(m_filename == "") return 0;
    FILE* lFile = fopen(m_filename.c_str(), _openType.c_str());
    return lFile;
}
//===============================================
FILE* GFile2::openFile(const GString2& _filename, const GString2& _openType) {
    FILE* lFile = fopen(_filename.c_str(), _openType.c_str());
    m_filename = _filename;
    m_openType = _openType;
    return lFile;
}
//===============================================
void GFile2::closeFile(FILE* _file) {
    fclose(_file);
}
//===============================================
