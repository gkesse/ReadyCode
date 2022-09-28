//===============================================
#ifndef _GFile_
#define _GFile_
//===============================================
#include "GObject.h"
//===============================================
class GFile : public GObject {
public:
    GFile();
    GFile(const QString& _filename);
    GFile(const QString& _filename, const QString& _openType);
    ~GFile();
    //
    bool existFile() const;
    QString getContent() const;
    void setContent(const QString& _data);
    //
    QString getAppendType() const;
    QString getLogFullname() const;
    QString getLogFullname(bool _isTestEnv) const;
    QString getScriptInFilename() const;
    QString getScriptOutFilename() const;
    QString getDateFullname(const QString& _key, const QString& _ext) const;
    QString getDateFilename(const QString& _key, const QString& _ext) const;
    QString getFilename(const QString& _key, const QString& _date, const QString& _ext) const;
    QString getFullname(const QString& _path, const QString& _filename) const;
    FILE* openLogFile();
    FILE* openFile();
    FILE* openFile(const QString& _openType);
    FILE* openFile(const QString& _filename, const QString& _openType);
    void closeFile(FILE* _file);

private:
    QString m_filename;
    QString m_openType;
};
//==============================================
#endif
//==============================================
