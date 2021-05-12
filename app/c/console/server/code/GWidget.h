//===============================================
#ifndef _GWidget_
#define _GWidget_
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//===============================================
typedef struct _GWidgetO GWidgetO;
//===============================================
struct _GWidgetO {
    void* child;
    void (*Delete)(GWidgetO* obj);
    void (*Click)(GWidgetO* obj);
    void (*EmitClick)(GWidgetO* obj);
    void (*OnClick)(GWidgetO* obj);
    void (*AddClick)(GWidgetO* obj, GWidgetO* obs);
    GWidgetO* item_map[8];
    int item_count;
};
//===============================================
GWidgetO* GWidget(const char* key);
GWidgetO* GWidget_New();
void GWidget_Delete(GWidgetO* obj);
//===============================================
#endif
//===============================================
