//===============================================
#include "GAdminUi.h"
#include "GXml.h"
//===============================================
static GObjectO* m_GAdminUiO = 0;
//===============================================
static void GAdminUi_delete(GObjectO* _obj);
static void GAdminUi_run(GObjectO* _obj, int _argc, char** _argv);
static void GAdminUi_createDom(GObjectO* _obj);
//===============================================
GObjectO* GAdminUi_new() {
    GObjectO* lParent = GObject_new();
    GAdminUiO* lChild = (GAdminUiO*)malloc(sizeof(GAdminUiO));

    lParent->child = lChild;
    lParent->delete = GAdminUi_delete;
    lParent->run = GAdminUi_run;

    GAdminUi_createDom(lParent);

    return lParent;
}
//===============================================
static void GAdminUi_delete(GObjectO* _obj) {
    GObject_delete(_obj);
}
//===============================================
GObjectO* GAdminUiI() {
    if(m_GAdminUiO == 0) {
        m_GAdminUiO = GAdminUi_new();
    }
    return m_GAdminUiO;
}
//===============================================
GAdminUiO* GAdminUiIO() {
    return GAdminUiI()->child;
}
//===============================================
static void GAdminUi_run(GObjectO* _obj, int _argc, char** _argv) {
    printf("[GAdminUi_run]..........\n");
}
//===============================================
static void GAdminUi_createDom(GObjectO* _obj) {
    _obj->m_dom = GXml_New();
    GObjectO* lDom = _obj->m_dom;
    GXmlO* lDomO = lDom->child;
    lDomO->loadXmlFile(lDom, "process.xml");
}
//===============================================
