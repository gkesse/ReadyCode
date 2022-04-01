//===============================================
#include "GFile.h"
#include "GFormat.h"
#include "GShell.h"
#include "GEnv.h"
#include "GDate.h"
//===============================================
GFile::GFile() : GObject() {
    m_filename = "";
    m_openType = "";
}
//===============================================
GFile::GFile(const std::string& _filename) : GObject() {
    m_filename = _filename;
    m_openType = "";
}
//===============================================
GFile::GFile(const std::string& _filename, const std::string& _openType) : GObject() {
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
std::string GFile::getContent() const {
    if(m_filename == "") return "";
    if(!existFile()) return "";
    std::ifstream lFile(m_filename);
    std::stringstream lBuffer;
    lBuffer << lFile.rdbuf();
    return lBuffer.str();
}
//===============================================
void GFile::setContent(const std::string& _data) {
    if(m_filename == "") return;
    std::ofstream lFile(m_filename);
    lFile << _data;
    lFile.close();
}
//===============================================
std::string GFile::getAppendType() const {
    return "a+";
}
//===============================================
std::string GFile::getLogFullname() const {
    std::string lFilename = getDateFullname("log_", ".txt");
    return lFilename;
}
//===============================================
std::string GFile::getScriptInFilename() const {
    std::string lFilename = getDateFilename("script_", "_in.txt");
    return lFilename;
}
//===============================================
std::string GFile::getScriptOutFilename() const {
    std::string lFilename = getDateFilename("script_", "_out.txt");
    return lFilename;
}
//===============================================
std::string GFile::getDateFullname(const std::string& _key, const std::string& _ext) const {
    std::string lTmpDir = GEnv().getTmpDir();
    std::string lFilename = getDateFilename(_key, _ext);
    lFilename = getFullname(lTmpDir, lFilename);
    return lFilename;
}
//===============================================
std::string GFile::getDateFilename(const std::string& _key, const std::string& _ext) const {
    std::string lDate = GDate().getDate(GDate().getDateFileFormat());
    return getFilename(_key, lDate, _ext);
}
//===============================================
std::string GFile::getFilename(const std::string& _key, const std::string& _date, const std::string& _ext) const {
    std::string lFilename = sformat("%s%s%s", _key.c_str(), _date.c_str(), _ext.c_str());
    return lFilename;
}
//===============================================
std::string GFile::getFullname(const std::string& _path, const std::string& _filename) const {
    GShell().createDir(_path);
    std::string lFilename = sformat("%s/%s", _path.c_str(), _filename.c_str());
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
FILE* GFile::openFile(const std::string& _openType) {
    if(m_filename == "") return 0;
    FILE* lFile = fopen(m_filename.c_str(), _openType.c_str());
    return lFile;
}
//===============================================
FILE* GFile::openFile(const std::string& _filename, const std::string& _openType) {
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
