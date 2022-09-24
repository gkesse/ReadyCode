//===============================================
#ifndef _GFile2_
#define _GFile2_
//===============================================
#include "GObject2.h"
//===============================================
class GFile2 : public GObject2 {
public:
    GFile2();
    GFile2(const GString2& _filename);
    GFile2(const GString2& _filename, const GString2& _openType);
    ~GFile2();
    //
    bool existFile() const;
    GString2 getContent() const;
    void setContent(const GString2& _data);
    //
    GString2 getAppendType() const;
    GString2 getLogFullname() const;
    GString2 getLogFullname(bool _isTestEnv) const;
    GString2 getScriptInFilename() const;
    GString2 getScriptOutFilename() const;
    GString2 getDateFullname(const GString2& _key, const GString2& _ext) const;
    GString2 getDateFilename(const GString2& _key, const GString2& _ext) const;
    GString2 getFilename(const GString2& _key, const GString2& _date, const GString2& _ext) const;
    GString2 getFullname(const GString2& _path, const GString2& _filename) const;
    FILE* openLogFile();
    FILE* openFile();
    FILE* openFile(const GString2& _openType);
    FILE* openFile(const GString2& _filename, const GString2& _openType);
    void closeFile(FILE* _file);

private:
    GString2 m_filename;
    GString2 m_openType;
};
//==============================================
#endif
//==============================================
