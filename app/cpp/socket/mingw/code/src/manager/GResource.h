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
    // app
    std::string app_name;
    // mcml
    std::string mcml_file;
    // shader
    std::string shader_vertex_file;
    std::string shader_fragment_file;
    // texture
    std::string texture_file;
    std::string texture_file_2;
    // image
    std::string image_file;
    // xml
    std::string xml_file;
};
//==============================================
#endif
//==============================================
