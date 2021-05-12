//===============================================
#include "GWidget.h"
#include "GButton.h"
#include "GLed.h"
//===============================================
static void GWidget_Click(GWidgetO* obj);
static void GWidget_EmitClick(GWidgetO* obj);
static void GWidget_OnClick(GWidgetO* obj);
static void GWidget_AddClick(GWidgetO* obj, GWidgetO* obs);
//===============================================
GWidgetO* GWidget_New() {
    GWidgetO* lObj = (GWidgetO*)malloc(sizeof(GWidgetO));
    
    lObj->item_count = 0;
    
    lObj->Delete = GWidget_Delete;
    lObj->Click = GWidget_Click;
    lObj->EmitClick = GWidget_EmitClick;
    lObj->OnClick = GWidget_OnClick;
    lObj->AddClick = GWidget_AddClick;
    return lObj;
}
//===============================================
void GWidget_Delete(GWidgetO* obj) {
    free(obj);
}
//===============================================
GWidgetO* GWidget(const char* key) {
    if(!strcmp(key, "widget")) {return GWidget_New();}
    if(!strcmp(key, "button")) {return GButton_New();}
    if(!strcmp(key, "led")) {return GLed_New();}
    return GWidget_New();
}
//===============================================
static void GWidget_EmitClick(GWidgetO* obj) {
    for(int i = 0; i < obj->item_count; i++) {
        GWidgetO* lObj = obj->item_map[i];
        lObj->OnClick(lObj);
    }
}
//===============================================
static void GWidget_AddClick(GWidgetO* obj, GWidgetO* obs) {
    obs->item_map[obs->item_count] = obj;
    obs->item_count++;
}
//===============================================
static void GWidget_Click(GWidgetO* obj) {}
static void GWidget_OnClick(GWidgetO* obj) {}
//===============================================
