//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _sGManager sGManager;
typedef struct _sGApp sGApp;
//===============================================
class GManager {
private:
    GManager();
    
public:
    ~GManager();
    static GManager* Instance();
    sGManager* data();

private:
    static GManager* m_instance;
    sGManager* mgr;
};
//==============================================
struct _sGManager {
    sGApp* app;
};
//==============================================
struct _sGApp {
    // app
    std::string app_name;
    // mcml
    std::string mcml_file;
    // shader
    std::string shader_vertex_file;
    std::string shader_fragment_file;
    // texture
    std::string texture_file;
    std::string texture_file2;
    // image
    std::string image_file;
    // video
    std::string video_file;
    std::string video_file2;
    // cascade
    std::string cascade_file;
    // train
    std::string train_file;
    // xml
    std::string xml_file;
};
//==============================================
#endif
//==============================================
