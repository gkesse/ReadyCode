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
std::string GFile::getData() const {
    std::ifstream lFile(m_filename);
    std::stringstream lBuffer;
    lBuffer << lFile.rdbuf();
    return lBuffer.str();
}
//===============================================
std::string GFile::getAppendType() const {
    return "a+";
}
//===============================================
std::string GFile::getLogFile() const {
    std::string lFilename = getDateFile("log", "txt");
    return lFilename;
}
//===============================================
std::string GFile::getScriptFile() const {
    std::string lFilename = getDateFile("script", "txt");
    return lFilename;
}
//===============================================
std::string GFile::getDateFile(const std::string& _key, const std::string& _ext) const {
    std::string lTmpDir = GEnv().getTmpDir();
    std::string lDate = GDate().getDate(GDate().getDateFileFormat());
    std::string lFilename = getFilename(_key, lDate, _ext);
    lFilename = getFilename(lTmpDir, lFilename);
    return lFilename;
}
//===============================================
std::string GFile::getFilename(const std::string& _key, const std::string& _date, const std::string& _ext) const {
    std::string lFilename = sformat("%s_%s.%s", _key.c_str(), _date.c_str(), _ext.c_str());
    return lFilename;
}
//===============================================
std::string GFile::getFilename(const std::string& _path, const std::string& _filename) const {
    GShell().createDir(_path);
    std::string lFilename = sformat("%s/%s", _path.c_str(), _filename.c_str());
    return lFilename;
}
//===============================================
FILE* GFile::openLogFile() {
    FILE* lFile = openFile(getLogFile(), getAppendType());
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
    if(!_file) return;
    fclose(_file);
}
//===============================================
