//===============================================
#include "GResource.h"
#include "GLog.h"
//===============================================
GResource* GResource::m_instance = 0;
//===============================================
GResource::GResource() {
    // manager
    m_res = new sGResource;
    // app
    m_res->app = new sGApp;
    m_res->app->data_path = "C:/Users/Admin/Downloads/Programs/ReadyData/data";
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
const char* GResource::getPath(const std::string& _resource, const std::string& _filename) {
    std::string lPath = GAPP->data_path + "/" + _resource + "/" + _filename;
    return lPath.c_str();
}
//===============================================
void GResource::loadFileMap(const std::string& _path, const std::string& _resource, std::map<std::string, std::string>& _map) {
    struct dirent* lEntry;
    std::string lPath = _path + "/" + _resource;
    DIR* lDir = opendir(lPath.c_str());
    if (lDir == NULL) {
        GLOG->addError(GERR, "Erreur l'ouverture du repertoire a echoue : %s", lPath.c_str());
        return;
    }
    while ((lEntry = readdir(lDir)) != NULL) {
        std::string lFilename = lEntry->d_name;
        std::string lFullname = lPath + "/" + lFilename;
        _map[lFilename] = lFullname;
    }
    closedir(lDir);
}
//===============================================
