//===============================================
#include "GObject.h"
#include "GXml.h"
//===============================================
static void GObject_run(GObjectO* _obj, int _argc, char** _argv);
static int GObject_fsize(GObjectO* _obj, FILE* _file);
static char* GObject_getDataPath(GObjectO* _obj);
static char* GObject_getRepoPath(GObjectO* _obj, const char* _repo, const char* _filename);
//===============================================
GObjectO* GObject_new() {
    GObjectO* lObj = (GObjectO*)malloc(sizeof(GObjectO));

    lObj->child = lObj;
    lObj->delete = GObject_delete;
    lObj->run = GObject_run;
    lObj->fsize = GObject_fsize;
    lObj->getDataPath = GObject_getDataPath;
    lObj->getRepoPath = GObject_getRepoPath;

    lObj->m_path[0] = 0;
    lObj->m_dom = 0;

    return lObj;
}
//===============================================
void GObject_delete(GObjectO** _obj) {
    GObjectO* lObj = *_obj;
    if(lObj->m_dom) {
        lObj->m_dom->delete(&lObj->m_dom);
    }
    free(lObj->child);
    free(lObj);
    *_obj = 0;
}
//===============================================
static void GObject_run(GObjectO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
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
    char* lPath = getenv("GPROJECT_DATA");
    return lPath;
}
//===============================================
static char* GObject_getRepoPath(GObjectO* _obj, const char* _repo, const char* _filename) {
    int lIndex = 0;
    _obj->m_path[lIndex] = 0;
    if(_obj->getDataPath(_obj)) {
        lIndex += sprintf(&_obj->m_path[lIndex], "%s", _obj->getDataPath(_obj));
    }
    if(_repo) {
        if(lIndex == 0) {
            lIndex += sprintf(&_obj->m_path[lIndex], "%s", _repo);
        }
        else {
            lIndex += sprintf(&_obj->m_path[lIndex], "/%s", _repo);
        }
    }
    if(_filename) {
        if(lIndex == 0) {
            lIndex += sprintf(&_obj->m_path[lIndex], "%s", _filename);
        }
        else {
            lIndex += sprintf(&_obj->m_path[lIndex], "/%s", _filename);
        }
    }
    return _obj->m_path;
}
//===============================================
