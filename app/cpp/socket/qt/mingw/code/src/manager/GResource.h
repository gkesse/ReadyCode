//===============================================
#ifndef _GResource_
#define _GResource_
//===============================================
#include "GInclude.h"
//===============================================
struct sGResource;
struct sGApp;
//===============================================
class GResource {
private:
    GResource();
    
public:
    ~GResource();
    static GResource* Instance();
    sGResource* data();

private:
    static GResource* m_instance;
    sGResource* m_res;
};
//==============================================
struct sGResource {
    sGApp* app;
};
//==============================================
struct sGApp {
    // xml
    std::string xml_file;
};
//==============================================
#endif
//==============================================
