//===============================================
#include "GAdmin.h"
//===============================================
static void GAdmin_delete(GAdminO* _obj);
static void GAdmin_run(GAdminO* _obj, int _argc, char** _argv);
static void GAdmin_runInit(GAdminO* _obj, int _argc, char** _argv);
static void GAdmin_runMethod(GAdminO* _obj, int _argc, char** _argv);
static void GAdmin_runChoice(GAdminO* _obj, int _argc, char** _argv);
static void GAdmin_runTask(GAdminO* _obj, int _argc, char** _argv);
static void GAdmin_runQuit(GAdminO* _obj, int _argc, char** _argv);
//===============================================
GAdminO* GAdmin_new() {
    GObjectO* lParent = GObject_new();
    GAdminO* lChild = (GAdminO*)malloc(sizeof(GAdminO));

    lChild->parent = lParent;
    lChild->delete = GAdmin_delete;
    lChild->run = GAdmin_run;

    lParent->child = lChild;

    return lChild;
}
//===============================================
static void GAdmin_delete(GAdminO* _obj) {
    GObject_delete(_obj->parent);
}
//===============================================
static void GAdmin_run(GAdminO* _obj, int _argc, char** _argv) {
    _obj->m_state = "init";
    while(1) {
        if(!strcmp(_obj->m_state, "init")) {
            GAdmin_runInit(_obj, _argc, _argv);
        }
        else if(!strcmp(_obj->m_state, "method")) {
            GAdmin_runMethod(_obj, _argc, _argv);
        }
        else if(!strcmp(_obj->m_state, "choice")) {
            GAdmin_runChoice(_obj, _argc, _argv);
        }
        else if(!strcmp(_obj->m_state, "task")) {
            GAdmin_runTask(_obj, _argc, _argv);
        }
        else if(!strcmp(_obj->m_state, "quit")) {
            GAdmin_runQuit(_obj, _argc, _argv);
        }
        else break;
    }
}
//===============================================
static void GAdmin_runInit(GAdminO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    _obj->m_state = "method";
}
//===============================================
static void GAdmin_runMethod(GAdminO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    _obj->m_state = "choice";
}
//===============================================
static void GAdmin_runChoice(GAdminO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    _obj->m_state = "task";
}
//===============================================
static void GAdmin_runTask(GAdminO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    _obj->m_state = "quit";
}
//===============================================
static void GAdmin_runQuit(GAdminO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    _obj->m_state = "end";
}
//===============================================
