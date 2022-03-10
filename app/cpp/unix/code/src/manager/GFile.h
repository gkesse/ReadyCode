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
    ~GFile();
    //
    std::string getData() const ;

private:
    std::string m_filename;
};
//==============================================
#endif
//==============================================
