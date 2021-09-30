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
    void openFile();
    void openFile2();
    int writeData(const char* data, int size);
    int writeData(const GString& data);
    int readData(char* data, int size);
    void closeFile();
    
private:
    std::string m_filename;
    int m_fileId;
};
//==============================================
#endif
//==============================================
