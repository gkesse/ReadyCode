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
    mgr->app->shader_vertex_file = "data/shader/simple.vert";
    mgr->app->shader_fragment_file = "data/shader/simple.frag";
    mgr->app->texture_file = "data/texture/container.jpg";
    mgr->app->texture_file2 = "data/texture/awesomeface.png";
    mgr->app->image_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\img\\equipe_de_france.jpg";
    mgr->app->image_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\img\\fruits.jpg";
    mgr->app->video_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\video\\football_americain.avi";
    mgr->app->video_file2 = "C:\\Users\\Admin\\Downloads\\RData\\data\\video\\football_americain_canny.avi";
    mgr->app->cascade_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\cascade\\haarcascade_eye.xml";
    mgr->app->cascade_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\cascade\\haarcascade_frontalface_default.xml";
    mgr->app->cascade_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\cascade\\haarcascade_frontalface_alt.xml";
    mgr->app->train_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\train\\agaricus-lepiota.data";
    mgr->app->xml_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\xml\\catalog.xml";
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
