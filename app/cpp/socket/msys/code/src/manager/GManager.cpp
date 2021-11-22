//===============================================
#include "GManager.h"
//===============================================
GResource* GResource::m_instance = 0;
//===============================================
GResource::GResource() {
    // manager
    m_res = new sGResource;
    // app
    m_res->app = new sGApp;
    m_res->app->app_name = "ReadyApp";
    m_res->app->mcml_file = "data/mcml/MCML_output.txt";
    m_res->app->shader_vertex_file = "data/shader/simple.vert";
    m_res->app->shader_fragment_file = "data/shader/simple.frag";
    m_res->app->texture_file = "data/texture/container.jpg";
    m_res->app->texture_file2 = "data/texture/awesomeface.png";
    m_res->app->image_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\img\\equipe_de_france.jpg";
    m_res->app->image_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\img\\fruits.jpg";
    m_res->app->video_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\video\\football_americain.avi";
    m_res->app->video_file2 = "C:\\Users\\Admin\\Downloads\\RData\\data\\video\\football_americain_canny.avi";
    m_res->app->cascade_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\cascade\\haarcascade_eye.xml";
    m_res->app->cascade_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\cascade\\haarcascade_frontalface_default.xml";
    m_res->app->cascade_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\cascade\\haarcascade_frontalface_alt.xml";
    m_res->app->train_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\train\\agaricus-lepiota.data";
    m_res->app->xml_file = "C:\\Users\\Admin\\Downloads\\RData\\data\\xml\\catalog.xml";
    m_res->app->curl_url = "http://www.google.com";
    m_res->app->curl_url = "https://raw.githubusercontent.com/gkesse/ReadyCode/main/app/cpp/socket/unix/code/src/main.cpp";
}
//===============================================
GResource::~GResource() {

}
//===============================================
GResource* GResource::Instance() {
    if(m_instance == 0) {
        m_instance = new GResource;
    }
    return m_instance;
}
//===============================================
sGResource* GResource::getData() {
    return m_res;
}
//===============================================
