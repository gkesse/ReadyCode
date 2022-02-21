//===============================================
#include "GList.h"
#include "GXml.h"
//===============================================
static void GList_delete(GListO* _obj);
static void GList_run(GListO* _obj, int _argc, char** _argv);
static void GList_runTest(GListO* _obj, int _argc, char** _argv);
//===============================================
GListO* GList_new() {
    GObjectO* lParent = GObject_new();
    GListO* lChild = (GListO*)malloc(sizeof(GListO));

    lChild->parent = lParent;
    lChild->delete = GList_delete;
    lChild->run = GList_run;

    lParent->child = lChild;

    return lChild;
}
//===============================================
static void GList_delete(GListO* _obj) {
    GObject_delete(_obj->parent);
}
//===============================================
static void GList_run(GListO* _obj, int _argc, char** _argv) {
    char* lKey = "default";
    //
    if(_argc > 2) {
        lKey = _argv[2];
    }
    //
    if(!strcmp(lKey, "test")) {
        GList_runTest(_obj, _argc, _argv);
    }
}
//===============================================
static void GList_runTest(GListO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GXmlO* lDom = GXml_new();
    lDom->createDoc(lDom, "rdv");
    lDom->getRoot(lDom, "rdv");
    printf("%s\n", lDom->getNodeXml(lDom));
    lDom->delete(lDom);
}
//===============================================
