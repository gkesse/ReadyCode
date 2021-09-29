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
    void setFilename(const std::string& filename);
    int getSize() const;
    
private:
    std::string m_filename;
};
//==============================================
#endif
//==============================================
