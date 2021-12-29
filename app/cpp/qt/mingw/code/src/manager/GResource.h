//===============================================
#ifndef _GResource_
#define _GResource_
//===============================================
#include "GInclude.h"
//===============================================
struct sGResource;
struct sGApp;
//===============================================
#define GRES GResource::Instance()
#define GAPP GRES->getData()->app
#define GPATH(_x, _y) GRES->getPath(_x, _y)
#define GIMG(_x) GPATH("img", _x)
//===============================================
class GResource {
private:
    GResource();
    
public:
    ~GResource();
    static GResource* Instance();
    sGResource* getData();
    const char* getPath(const std::string& _resource, const std::string& _filename);
    void loadFileMap(const std::string& _path, const std::string& _resource, std::map<std::string, std::string>& _map);

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
    // data
    std::string data_path;
    // xml
    std::string xml_file;
    // sqlite
    std::string sqlite_file;
};
//==============================================
#endif
//==============================================
