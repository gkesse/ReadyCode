//===============================================
#include "GLog.h"
//===============================================
static void GLog_delete(GLogO* _obj);
static void GLog_run(GLogO* _obj, int _argc, char** _argv);
static void GLog_runTest(GLogO* _obj, int _argc, char** _argv);
//===============================================
GLogO* GLog_new() {
    GObjectO* lParent = GObject_new();
    GLogO* lChild = (GLogO*)malloc(sizeof(GLogO));

    lChild->parent = lParent;
    lChild->delete = GLog_delete;
    lChild->run = GLog_run;

    lParent->child = lChild;

    return lChild;
}
//===============================================
static void GLog_delete(GLogO* _obj) {
    GObject_delete(_obj->parent);
}
//===============================================
static void GLog_run(GLogO* _obj, int _argc, char** _argv) {
    char* lKey = "default";
    //
    if(_argc > 2) {
        lKey = _argv[2];
    }
    //
    if(!strcmp(lKey, "test")) {
        GLog_runTest(_obj, _argc, _argv);
    }
}
//===============================================
static void GLog_runTest(GLogO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
}
//===============================================
