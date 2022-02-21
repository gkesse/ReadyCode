//===============================================
#include "GProcess.h"
#include "GTuto.h"
#include "GAdmin.h"
#include "GXml.h"
#include "GLog.h"
#include "GList.h"
//===============================================
static GProcessO* m_GProcessO = 0;
//===============================================
static void GProcess_delete(GProcessO* _obj);
static void GProcess_run(GProcessO* _obj, int _argc, char** _argv);
static void GProcess_runTuto(GProcessO* _obj, int _argc, char** _argv);
static void GProcess_runAdmin(GProcessO* _obj, int _argc, char** _argv);
static void GProcess_runXml(GProcessO* _obj, int _argc, char** _argv);
static void GProcess_runLog(GProcessO* _obj, int _argc, char** _argv);
static void GProcess_runList(GProcessO* _obj, int _argc, char** _argv);
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
    if(!strcmp(lKey, "tuto")) {
        GProcess_runTuto(_obj, _argc, _argv);
    }
    else if(!strcmp(lKey, "admin")) {
        GProcess_runAdmin(_obj, _argc, _argv);
    }
    else if(!strcmp(lKey, "xml")) {
        GProcess_runXml(_obj, _argc, _argv);
    }
    else if(!strcmp(lKey, "log")) {
        GProcess_runLog(_obj, _argc, _argv);
    }
    else if(!strcmp(lKey, "list")) {
        GProcess_runList(_obj, _argc, _argv);
    }
}
//===============================================
static void GProcess_runTuto(GProcessO* _obj, int _argc, char** _argv) {
    GTutoO* lTuto = GTuto_new();
    lTuto->run(lTuto, _argc, _argv);
    lTuto->delete(lTuto);
}
//===============================================
static void GProcess_runAdmin(GProcessO* _obj, int _argc, char** _argv) {
    GAdminO* lAdmin = GAdmin_new();
    lAdmin->run(lAdmin, _argc, _argv);
    lAdmin->delete(lAdmin);
}
//===============================================
static void GProcess_runXml(GProcessO* _obj, int _argc, char** _argv) {
    GXmlO* lXml = GXml_new();
    lXml->run(lXml, _argc, _argv);
    lXml->delete(lXml);
}
//===============================================
static void GProcess_runLog(GProcessO* _obj, int _argc, char** _argv) {
    GLogO* lLog = GLog_new();
    lLog->run(lLog, _argc, _argv);
    lLog->delete(lLog);
}
//===============================================
static void GProcess_runList(GProcessO* _obj, int _argc, char** _argv) {
    GListO* lList = GList_new();
    lList->run(lList, _argc, _argv);
    lList->delete(lList);
}
