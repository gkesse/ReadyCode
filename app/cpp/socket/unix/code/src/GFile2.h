//===============================================
#ifndef _GFile2_
#define _GFile2_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GFile2 {
public:
    GFile2();
    ~GFile2();
    void setFilename(const std::string& filename);
    void open();
    void write(const char* data, int size);
    void write(const GString& data);
    
private:
    std::string m_filename;
    int m_fileId;
};
//==============================================
#endif
//==============================================
