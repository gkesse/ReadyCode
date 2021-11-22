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
    m_res->app->xml_file = "C:/Users/Admin/Downloads/Programs/ReadyData/data/xml/catalog_02.xml";
    m_res->app->sqlite_file = "C:/Users/Admin/Downloads/Programs/ReadyData/data/sqlite/database.dat";
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
