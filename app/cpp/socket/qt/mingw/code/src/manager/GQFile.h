//===============================================
#ifndef _GFile_
#define _GFile_
//===============================================
#include "GInclude.h"
//===============================================
class GQFile {
public:
    GQFile();
    ~GQFile();
    void openRead(const QString& _filename);
    void openWrite(const QString& _filename);
    QFile file();
    void close();

private:
    QFile m_file;
};
//==============================================
#endif
//==============================================
