//===============================================
#include "GResource.h"
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
    m_res->app->shader_vertex_file = "C:/Users/Admin/Downloads/Programs/ReadyData/data/shader/wood.vs";
    m_res->app->shader_fragment_file = "C:/Users/Admin/Downloads/Programs/ReadyData/data/shader/wood.fs";
    m_res->app->texture_file = "data/texture/container.jpg";
    m_res->app->texture_file_2 = "data/texture/awesomeface.png";
    m_res->app->xml_file = "C:/Users/Admin/Downloads/Programs/ReadyData/data/xml/catalog_03.xml";
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
sGResource* GResource::data() {
    return m_res;
}
//===============================================
