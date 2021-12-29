//===============================================
#include "GProcess.h"
#include "GXml.h"
#include "GAdminUi.h"
//===============================================
static GObjectO* m_GProcessO = 0;
//===============================================
static void GProcess_delete(GObjectO* _obj);
static void GProcess_run(GObjectO* _obj, int _argc, char** _argv);
static void GProcess_runAdmin(GObjectO* _obj, int _argc, char** _argv);
static void GProcess_createDom(GObjectO* _obj);
static char* GProcess_getName(GObjectO* _obj);
static char* GProcess_getId(GObjectO* _obj);
static int GProcess_countProcess(GObjectO* _obj);
static char* GProcess_getIdIndex(GObjectO* _obj, int _index);
static char* GProcess_getNameIndex(GObjectO* _obj, int _index);
//===============================================
GObjectO* GProcess_new() {
    GObjectO* lParent = GObject_new();
    GProcessO* lChild = (GProcessO*)malloc(sizeof(GProcessO));

    lParent->child = lChild;
    lParent->delete = GProcess_delete;
    lParent->run = GProcess_run;

    GProcess_createDom(lParent);

    return lParent;
}
//===============================================
static void GProcess_delete(GObjectO* _obj) {
    GObject_delete(_obj);
}
//===============================================
GObjectO* GProcessI() {
    if(m_GProcessO == 0) {
        m_GProcessO = GProcess_new();
    }
    return m_GProcessO;
}
//===============================================
GProcessO* GProcessIO() {
    return GProcessI()->child;
}
//===============================================
static void GProcess_run(GObjectO* _obj, int _argc, char** _argv) {
    char* lKey = GProcess_getName(_obj);
    printf("-> %s\n", lKey);
    if(!strcmp(lKey, "console")) {

    }
    else if(!strcmp(lKey, "admin")) {
        GProcess_runAdmin(_obj, _argc, _argv);
    }
}
//===============================================
static void GProcess_runAdmin(GObjectO* _obj, int _argc, char** _argv) {
    GAdminUiI()->run(GAdminUiI(), _argc, _argv);
}
//===============================================
static void GProcess_createDom(GObjectO* _obj) {
    _obj->m_dom = GXml_New();
    GObjectO* lDom = _obj->m_dom;
    GXmlO* lDomO = lDom->child;
    lDomO->loadXmlFile(lDom, "process.xml");
}
//===============================================
static char* GProcess_getName(GObjectO* _obj) {
    GObjectO* lDom = _obj->m_dom;
    GXmlO* lDomO = lDom->child;
    //
    if(strcmp(GProcess_getId(_obj), "")) {
        char lId[16];
        sprintf(lId, "%s", GProcess_getId(_obj));
        for(int i = 0; i < GProcess_countProcess(_obj); i++) {
            if(!strcmp(lId, GProcess_getIdIndex(_obj, i))) {
                return GProcess_getNameIndex(_obj, i);
            }
        }
    }
    //
    lDomO->getRoot(lDom, "rdv")->getNode(lDom, "process");
    lDomO->getNode(lDom, "name");
    char* lData = lDomO->getNodeValue(lDom);
    //
    return lData;
}
//===============================================
static char* GProcess_getId(GObjectO* _obj) {
    GObjectO* lDom = _obj->m_dom;
    GXmlO* lDomO = lDom->child;
    lDomO->getRoot(lDom, "rdv")->getNode(lDom, "process");
    lDomO->getNodeEmpty(lDom, "id");
    char* lData = lDomO->getNodeValue(lDom);
    return lData;
}
//===============================================
static int GProcess_countProcess(GObjectO* _obj) {
    GObjectO* lDom = _obj->m_dom;
    GXmlO* lDomO = lDom->child;
    lDomO->getRoot(lDom, "rdv")->getNode(lDom, "process");
    lDomO->getNodeEmpty(lDom, "map");
    int lData = lDomO->countNode(lDom, "process");
    return lData;
}
//===============================================
static char* GProcess_getIdIndex(GObjectO* _obj, int _index) {
    GObjectO* lDom = _obj->m_dom;
    GXmlO* lDomO = lDom->child;
    lDomO->getRoot(lDom, "rdv")->getNode(lDom, "process");
    lDomO->getNodeEmpty(lDom, "map")->getNodeIndex(lDom, "process", _index);
    lDomO->getNodeEmpty(lDom, "id");
    char* lData = lDomO->getNodeValue(lDom);
    return lData;
}
//===============================================
static char* GProcess_getNameIndex(GObjectO* _obj, int _index) {
    GObjectO* lDom = _obj->m_dom;
    GXmlO* lDomO = lDom->child;
    lDomO->getRoot(lDom, "rdv")->getNode(lDom, "process");
    lDomO->getNodeEmpty(lDom, "map")->getNodeIndex(lDom, "process", _index);
    lDomO->getNodeEmpty(lDom, "name");
    char* lData = lDomO->getNodeValue(lDom);
    return lData;
}
//===============================================
