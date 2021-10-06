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
    void filename(const std::string& _filename);
    int size() const;
    void open();
    void close();
    int read(const char* format, ...);
    
private:
    std::string m_filename;
    FILE* m_pFile;
};
//==============================================
#endif
//==============================================
