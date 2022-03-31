//===============================================
#ifndef _GFile_
#define _GFile_
//===============================================
#include "GObject.h"
//===============================================
class GFile : public GObject {
public:
    GFile();
    GFile(const std::string& _filename);
    GFile(const std::string& _filename, const std::string& _openType);
    ~GFile();
    //
    bool existFile() const;
    std::string getContent() const;
    //
    std::string getAppendType() const;
    std::string getLogFile() const;
    std::string getScriptFile() const;
    std::string getDateFile(const std::string& _key, const std::string& _ext) const;
    std::string getFilename(const std::string& _key, const std::string& _date, const std::string& _ext) const;
    std::string getFilename(const std::string& _path, const std::string& _filename) const;
    FILE* openLogFile();
    FILE* openFile();
    FILE* openFile(const std::string& _openType);
    FILE* openFile(const std::string& _filename, const std::string& _openType);
    void closeFile(FILE* _file);

private:
    std::string m_filename;
    std::string m_openType;
};
//==============================================
#endif
//==============================================
