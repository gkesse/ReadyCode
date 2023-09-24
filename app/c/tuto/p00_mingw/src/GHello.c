//===============================================
#include "GHello.h"
//===============================================
static void GHello_delete(GHello** _this);
static void GHello_sayHello();
//===============================================
GHello* GHello_new() {
    GHello* lObj = (GHello*)malloc(sizeof(GHello));
    GHello_init(lObj);
    return lObj;
}
//===============================================
void GHello_init(GHello* _this) {
    assert(_this);
    _this->delete = GHello_delete;
    _this->sayHello = GHello_sayHello;
}
//===============================================
static void GHello_delete(GHello** _this) {
    assert(*_this);
    free(*_this);
    (*_this) = 0;
}
//===============================================
static void GHello_sayHello() {
    printf("Bonjour tout le monde.\n");
}
//===============================================
