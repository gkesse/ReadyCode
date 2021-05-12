//===============================================
#include "GLed.h"
//===============================================
static void GLed_Delete(GWidgetO* obj);
static void GLed_OnClick(GWidgetO* obj);
//===============================================
GWidgetO* GLed_New() {
    GWidgetO* lParent = GWidget_New();
    GLedO* lChild = (GLedO*)malloc(sizeof(GLedO));

    lChild->state = "off";

    lParent->child = lChild;
    lParent->Delete = GLed_Delete;
    lParent->OnClick = GLed_OnClick;
    return lParent;
}
//===============================================
static void GLed_Delete(GWidgetO* obj) {
    GWidget_Delete(obj);
}
//===============================================
static void GLed_OnClick(GWidgetO* obj) {
    GLedO* lObj = obj->child;
    if(!strcmp(lObj->state, "off")) {
        printf("Je fais allumer la LED [ON]\n");
        lObj->state = "on";
    }
    else if(!strcmp(lObj->state, "on")) {
        printf("Je fais eteindre la LED [OFF]\n");
        lObj->state = "off";
    }
}
//===============================================
