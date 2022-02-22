//===============================================
#include "GLog.h"
//===============================================
static void GLog_delete(GLogO** _obj);
//===============================================
GLogO* GLog_new() {
    GObjectO* lParent = GObject_new();
    GLogO* lChild = (GLogO*)malloc(sizeof(GLogO));

    lChild->parent = lParent;
    lChild->delete = GLog_delete;

    lParent->child = lChild;

    return lChild;
}
//===============================================
static void GLog_delete(GLogO** _obj) {
    GLogO* lObj = *_obj;
    lObj->parent->delete(&lObj->parent);
    *_obj = 0;
}
//===============================================
