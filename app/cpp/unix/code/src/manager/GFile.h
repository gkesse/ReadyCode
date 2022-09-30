//===============================================
#ifndef _GFile_
#define _GFile_
//===============================================
#include "GObject.h"
//===============================================
class GFile : public GObject {
public:
    GFile();
    GFile(const GString& _filename);
    GFile(const GString& _filename, const GString& _openType);
    ~GFile();
    //
    bool existFile() const;
    GString getContent() const;
    void setContent(const GString& _data);
    //
    GString getAppendType() const;
    GString getLogFullname() const;
    GString getLogFullname(bool _isTestEnv) const;
    GString getScriptInFilename() const;
    GString getScriptOutFilename() const;
    GString getDateFullname(const GString& _key, const GString& _ext) const;
    GString getDateFilename(const GString& _key, const GString& _ext) const;
    GString getFilename(const GString& _key, const GString& _date, const GString& _ext) const;
    GString getFullname(const GString& _path, const GString& _filename) const;
    FILE* openLogFile();
    FILE* openFile();
    FILE* openFile(const GString& _openType);
    FILE* openFile(const GString& _filename, const GString& _openType);
    void closeFile(FILE* _file);

private:
    GString m_filename;
    GString m_openType;
};
//==============================================
#endif
//==============================================
