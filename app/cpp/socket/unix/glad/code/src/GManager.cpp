//===============================================
#include "GManager.h"
//===============================================
GManager* GManager::m_instance = 0;
//===============================================
GManager::GManager() {
    // manager
    mgr = new sGManager;
    // app
    mgr->app = new sGApp;
    mgr->app->app_name = "ReadyApp";
    mgr->app->text_file = "/home/rpi4/Programs/ReadyData/data/text/test.txt";
    mgr->app->shader_vertex_file = "/home/rpi4/Programs/ReadyData/data/shader/diffuse.vert";
    mgr->app->shader_fragment_file = "/home/rpi4/Programs/ReadyData/data/shader/diffuse.frag";
    mgr->app->shader_fragment_file_2 = "/home/rpi4/Programs/ReadyData/data/shader/separable2.frag.glsl";
}
//===============================================
GManager::~GManager() {

}
//===============================================
GManager* GManager::Instance() {
    if(m_instance == 0) {
        m_instance = new GManager;
    }
    return m_instance;
}
//===============================================
sGManager* GManager::data() {
    return mgr;
}
//===============================================
