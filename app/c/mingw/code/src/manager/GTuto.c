//===============================================
#include "GTuto.h"
//===============================================
static void GTuto_delete(GTutoO** _obj);
static void GTuto_run(GTutoO* _obj, int _argc, char** _argv);
static void GTuto_runTest(GTutoO* _obj, int _argc, char** _argv);
//===============================================
GTutoO* GTuto_new() {
    GObjectO* lParent = GObject_new();
    GTutoO* lChild = (GTutoO*)malloc(sizeof(GTutoO));

    lChild->parent = lParent;
    lChild->delete = GTuto_delete;
    lChild->run = GTuto_run;

    lParent->child = lChild;

    return lChild;
}
//===============================================
static void GTuto_delete(GTutoO** _obj) {
    GTutoO* lObj = *_obj;
    GObject_delete(lObj->parent);
    *_obj = 0;
}
//===============================================
static void GTuto_run(GTutoO* _obj, int _argc, char** _argv) {
    char* lKey = "default";
    //
    if(_argc > 2) {
        lKey = _argv[2];
    }
    //
    if(!strcmp(lKey, "test")) {
        GTuto_runTest(_obj, _argc, _argv);
    }
}
//===============================================
static void GTuto_runTest(GTutoO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    printf("Bonjour tout le monde\n");
}
//===============================================
