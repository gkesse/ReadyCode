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
    mgr->app->mcml_file = "data/mcml/MCML_output.txt";
    mgr->app->shader_vertex_file = "C:/Users/Admin/Downloads/Programs/ReadyData/data/shader/wood.vs";
    mgr->app->shader_fragment_file = "C:/Users/Admin/Downloads/Programs/ReadyData/data/shader/wood.fs";
    mgr->app->texture_file = "data/texture/container.jpg";
    mgr->app->texture_file2 = "data/texture/awesomeface.png";
    mgr->app->texture_file2 = "C:/Users/Admin/Downloads/RData/data/img/fruits.jpg";
    mgr->app->xml_file = "C:/Users/Admin/Downloads/Programs/ReadyData/data/xml/catalog_03.xml";
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
