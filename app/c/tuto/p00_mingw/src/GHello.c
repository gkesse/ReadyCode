//===============================================
#include "GHello.h"
//===============================================
static void GHello_delete(GHello** _obj);
static void GHello_sayHello();
//===============================================
GHello* GHello_new() {
    GHello* lObj = (GHello*)malloc(sizeof(GHello));
    GHello_init(lObj);
    return lObj;
}
//===============================================
static void GHello_delete(GHello** _obj) {
    free(*_obj);
    (*_obj) = 0;
}
//===============================================
void GHello_init(GHello* _obj) {
    _obj->delete = GHello_delete;
    _obj->sayHello = GHello_sayHello;
}
//===============================================
static void GHello_sayHello() {
    printf("Bonjour tout le monde.\n");
}
//===============================================
