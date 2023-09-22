//===============================================
#include "GTest.h"
#include "GHello.h"
//===============================================
static void GTest_delete(GTest** _obj);
static void GTest_run(int _argc, char** _argv);
//===============================================
GTest* GTest_new() {
    GTest* lObj = (GTest*)malloc(sizeof(GTest));
    GTest_init(lObj);
    return lObj;
}
//===============================================
static void GTest_delete(GTest** _obj) {
    free(*_obj);
    (*_obj) = 0;
}
//===============================================
void GTest_init(GTest* _obj) {
    _obj->delete = GTest_delete;
    _obj->run = GTest_run;
}
//===============================================
static void GTest_run(int _argc, char** _argv) {
    printf("Je suis le module de test.\n");
}
//===============================================
