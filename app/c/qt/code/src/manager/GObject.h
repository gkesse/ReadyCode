//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GObjectO GObjectO;
//===============================================
struct _GObjectO {
    void* child;
    void (*delete)(GObjectO* _obj);
    void (*run)(GObjectO* _obj, int _argc, char** _argv);
    int (*fsize)(GObjectO* _obj, FILE* _file);
    char* (*getDataPath)(GObjectO* _obj);
    char* (*getRepoPath)(GObjectO* _obj, const char* _repo, const char* _filename);
    char* (*getXmlPath)(GObjectO* _obj, const char* _filename);
    //
    char m_path[256];
    GObjectO* m_dom;
};
//===============================================
GObjectO* GObject_new();
void GObject_delete(GObjectO* _obj);
//===============================================
#endif
//===============================================
