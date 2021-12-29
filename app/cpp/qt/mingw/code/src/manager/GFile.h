//===============================================
#ifndef _GFile_
#define _GFile_
//===============================================
#include "GInclude.h"
//===============================================
class GFile {
public:
    GFile();
    ~GFile();
    void openRead(const QString& _filename);
    void openWrite(const QString& _filename);
    QFile& file();
    void close();

private:
    QFile m_file;
};
//==============================================
#endif
//==============================================
