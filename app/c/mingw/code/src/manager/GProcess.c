//===============================================
#include "GProcess.h"
#include "GTuto.h"
#include "GAdmin.h"
#include "GTest.h"
//===============================================
static GProcessO* m_GProcessO = 0;
//===============================================
static void GProcess_delete(GProcessO* _obj);
static void GProcess_run(GProcessO* _obj, int _argc, char** _argv);
static void GProcess_runTest(GProcessO* _obj, int _argc, char** _argv);
static void GProcess_runTuto(GProcessO* _obj, int _argc, char** _argv);
static void GProcess_runAdmin(GProcessO* _obj, int _argc, char** _argv);
//===============================================
GProcessO* GProcess_new() {
    GObjectO* lParent = GObject_new();
    GProcessO* lChild = (GProcessO*)malloc(sizeof(GProcessO));

    lChild->parent = lParent;
    lChild->delete = GProcess_delete;
    lChild->run = GProcess_run;

    lParent->child = lChild;

    return lChild;
}
//===============================================
static void GProcess_delete(GProcessO* _obj) {
    GObject_delete(_obj->parent);
}
//===============================================
GProcessO* GProcess() {
    if(m_GProcessO == 0) {
        m_GProcessO = GProcess_new();
    }
    return m_GProcessO;
}
//===============================================
static void GProcess_run(GProcessO* _obj, int _argc, char** _argv) {
    char* lKey = "default";
    //
    if(_argc > 1) {
        lKey = _argv[1];
    }
    //
    if(!strcmp(lKey, "test")) {
        GProcess_runTest(_obj, _argc, _argv);
    }
    else if(!strcmp(lKey, "tuto")) {
        GProcess_runTuto(_obj, _argc, _argv);
    }
    else if(!strcmp(lKey, "admin")) {
        GProcess_runAdmin(_obj, _argc, _argv);
    }
}
//===============================================
static void GProcess_runTest(GProcessO* _obj, int _argc, char** _argv) {
    GTestO* lObj = GTest_new();
    lObj->run(lObj, _argc, _argv);
    lObj->delete(lObj);
}
//===============================================
static void GProcess_runTuto(GProcessO* _obj, int _argc, char** _argv) {
    GTutoO* lObj = GTuto_new();
    lObj->run(lObj, _argc, _argv);
    lObj->delete(lObj);
}
//===============================================
static void GProcess_runAdmin(GProcessO* _obj, int _argc, char** _argv) {
    GAdminO* lObj = GAdmin_new();
    lObj->run(lObj, _argc, _argv);
    lObj->delete(lObj);
}
//===============================================
