//===============================================
#include "GObject.h"
//===============================================
static void GObject_run(GObjectO* _obj, int _argc, char** _argv);
static int GObject_fsize(GObjectO* _obj, FILE* _file);
static char* GObject_getDataPath(GObjectO* _obj);
static char* GObject_getRepoPath(GObjectO* _obj, const char* _repo, const char* _filename);
static char* GObject_getXmlPath(GObjectO* _obj, const char* _filename);
//===============================================
GObjectO* GObject_new() {
    GObjectO* lObj = (GObjectO*)malloc(sizeof(GObjectO));

    lObj->child = lObj;
    lObj->delete = GObject_delete;
    lObj->run = GObject_run;
    lObj->fsize = GObject_fsize;
    lObj->getDataPath = GObject_getDataPath;
    lObj->getRepoPath = GObject_getRepoPath;
    lObj->getXmlPath = GObject_getXmlPath;

    lObj->m_path[0] = 0;
    lObj->m_dom = 0;

    return lObj;
}
//===============================================
void GObject_delete(GObjectO* _obj) {
    if(_obj->m_dom) {
        _obj->m_dom->delete(_obj->m_dom);
    }
    free(_obj->child);
    free(_obj);
}
//===============================================
static void GObject_run(GObjectO* _obj, int _argc, char** _argv) {
    printf("Execution de la fonction (%s)\n", __FUNCTION__);
}
//===============================================
static int GObject_fsize(GObjectO* _obj, FILE* _file) {
    fseek(_file, 0, SEEK_END);
    int lSize = ftell(_file);
    fseek(_file, 0, SEEK_SET);
    return lSize;
}
//===============================================
static char* GObject_getDataPath(GObjectO* _obj) {
    char* lPath = "C:/Users/Admin/Downloads/Programs/ReadyData/data";
    return lPath;
}
//===============================================
static char* GObject_getRepoPath(GObjectO* _obj, const char* _repo, const char* _filename) {
    sprintf(_obj->m_path, "%s/%s/%s", _obj->getDataPath(_obj), _repo, _filename);
    return _obj->m_path;
}
//===============================================
static char* GObject_getXmlPath(GObjectO* _obj, const char* _filename) {
    char* lPath = _obj->getRepoPath(_obj, "c/xml", _filename);
    return lPath;
}
//===============================================
