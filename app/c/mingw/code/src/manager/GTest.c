//===============================================
#include "GTest.h"
#include "GXml.h"
#include "GList.h"
#include "GMap.h"
//===============================================
GDECLARE_LIST(GINT)
GDEFINE_LIST(GINT)
GDECLARE_LIST(GCHAR_PTR)
GDEFINE_LIST(GCHAR_PTR)
GDECLARE_LIST(GVOID_PTR)
GDEFINE_LIST(GVOID_PTR)
//===============================================
GDECLARE_MAP(GINT, GCHAR_PTR)
GDEFINE_MAP(GINT, GCHAR_PTR)
GDECLARE_MAP(GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GCHAR_PTR, GVOID_PTR)
//===============================================
static void GTest_delete(GTestO** _obj);
static void GTest_run(GTestO* _obj, int _argc, char** _argv);
static void GTest_runTest(GTestO* _obj, int _argc, char** _argv);
//===============================================
static void GTest_runListInt(GTestO* _obj, int _argc, char** _argv);
static void GTest_runListChar(GTestO* _obj, int _argc, char** _argv);
static void GTest_runListVoid(GTestO* _obj, int _argc, char** _argv);
static void GTest_runMapIntChar(GTestO* _obj, int _argc, char** _argv);
static void GTest_runMapCharVoid(GTestO* _obj, int _argc, char** _argv);
//===============================================
static void GTest_runXmlNodeNamePrint(GTestO* _obj, int _argc, char** _argv);
static void GTest_runXmlNodeNamePrintChildren(GXmlO* _obj);
//===============================================
GTestO* GTest_new() {
    GObjectO* lParent = GObject_new();
    GTestO* lChild = (GTestO*)malloc(sizeof(GTestO));

    lChild->parent = lParent;
    lChild->delete = GTest_delete;
    lChild->run = GTest_run;
    //
    lParent->child = lChild;

    return lChild;
}
//===============================================
static void GTest_delete(GTestO** _obj) {
    GTestO* lObj = *_obj;
    lObj->parent->delete(&lObj->parent);
    *_obj = 0;
}
//===============================================
static void GTest_run(GTestO* _obj, int _argc, char** _argv) {
    char* lKey = "default";
    //
    if(_argc > 2) {
        lKey = _argv[2];
    }
    //
    if(!strcmp(lKey, "default")) {
        GTest_runTest(_obj, _argc, _argv);
    }
    // list
    else if(!strcmp(lKey, "list/int")) {
        GTest_runListInt(_obj, _argc, _argv);
    }
    else if(!strcmp(lKey, "list/char")) {
        GTest_runListChar(_obj, _argc, _argv);
    }
    else if(!strcmp(lKey, "list/void")) {
        GTest_runListVoid(_obj, _argc, _argv);
    }
    // map
    else if(!strcmp(lKey, "map/int/char")) {
        GTest_runMapIntChar(_obj, _argc, _argv);
    }
    else if(!strcmp(lKey, "map/char/void")) {
        GTest_runMapCharVoid(_obj, _argc, _argv);
    }
    // xml
    else if(!strcmp(lKey, "xml/node/name/print")) {
        GTest_runXmlNodeNamePrint(_obj, _argc, _argv);
    }
}
//===============================================
static void GTest_runTest(GTestO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);

    GListO(GINT)* lList = GList_new(GINT)();

    lList->addData(lList, 10);
    lList->addData(lList, 20);
    lList->addData(lList, 30);
    lList->addData(lList, 40);
    lList->addData(lList, 50);

    int lSize = lList->size(lList);

    for(int i = 0; i < lSize; i++) {
        int lData = lList->getData(lList, i);
        printf("%d\n", lData);
    }

    lList->delete(&lList);
}
//===============================================
static void GTest_runListInt(GTestO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);

    GListO(GINT)* lList = GList_new(GINT)();

    lList->addData(lList, 10);
    lList->addData(lList, 20);
    lList->addData(lList, 30);
    lList->addData(lList, 40);
    lList->addData(lList, 50);

    int lSize = lList->size(lList);

    for(int i = 0; i < lSize; i++) {
        int lData = lList->getData(lList, i);
        printf("%d\n", lData);
    }

    lList->delete(&lList);
}
//===============================================
static void GTest_runListChar(GTestO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);

    GListO(GCHAR_PTR)* lList = GList_new(GCHAR_PTR)();

    lList->addData(lList, "Un");
    lList->addData(lList, "Deux");
    lList->addData(lList, "Trois");
    lList->addData(lList, "Quatre");
    lList->addData(lList, "Cinq");

    int lSize = lList->size(lList);

    for(int i = 0; i < lSize; i++) {
        char* lData = lList->getData(lList, i);
        printf("%s\n", lData);
    }

    lList->delete(&lList);
}
//===============================================
static void GTest_runListVoid(GTestO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);

    GListO(GVOID_PTR)* lList = GList_new(GVOID_PTR)();

    for(int i = 0; i < 5; i++) {
        double* lData = (double*)malloc(sizeof(double));
        *lData = 3.14*(i + 1);
        lList->addData(lList, lData);
    }

    int lSize = lList->size(lList);

    for(int i = 0; i < lSize; i++) {
        double* lData = lList->getData(lList, i);
        printf("%.2f\n", *lData);
    }

    for(int i = 0; i < lSize; i++) {
        double* lData = lList->getData(lList, i);
        free(lData);
    }

    lList->delete(&lList);
}
//===============================================
static void GTest_runMapIntChar(GTestO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);

    GMapO(GINT, GCHAR_PTR)* lMap = GMap_new(GINT, GCHAR_PTR)();

    lMap->setData(lMap, 10, "Un x 10", 0);
    lMap->setData(lMap, 20, "Deux x 10", 0);
    lMap->setData(lMap, 30, "Trois x 10", 0);
    lMap->setData(lMap, 40, "Quatre x 10", 0);
    lMap->setData(lMap, 50, "Cinq x 10", 0);

    int lSize = lMap->size(lMap);

    for(int i = 0; i < lSize; i++) {
        int lKey = lMap->getKey(lMap, i);
        char* lValue = lMap->getData(lMap, lKey, 0);
        printf("%d : %s\n", lKey, lValue);
    }

    lMap->delete(&lMap);
}
//===============================================
static void GTest_runMapCharVoid(GTestO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);

    GMapO(GCHAR_PTR, GVOID_PTR)* lMap = GMap_new(GCHAR_PTR, GVOID_PTR)();

    double* lData;
    int i = 0;

    lData = (double*)malloc(sizeof(double));
    *lData = 3.14*(++i);
    lMap->setData(lMap, "Un", lData, lMap->equalChar);

    lData = (double*)malloc(sizeof(double));
    *lData = 3.14*(++i);
    lMap->setData(lMap, "Deux", lData, lMap->equalChar);

    lData = (double*)malloc(sizeof(double));
    *lData = 3.14*(++i);
    lMap->setData(lMap, "Trois", lData, lMap->equalChar);

    lData = (double*)malloc(sizeof(double));
    *lData = 3.14*(++i);
    lMap->setData(lMap, "Quatre", lData, lMap->equalChar);

    lData = (double*)malloc(sizeof(double));
    *lData = 3.14*(++i);
    lMap->setData(lMap, "Cinq", lData, lMap->equalChar);

    int lSize = lMap->size(lMap);

    for(int i = 0; i < lSize; i++) {
        char* lKey = lMap->getKey(lMap, i);
        double* lValue = lMap->getData(lMap, lKey, lMap->equalChar);
        printf("%s : %.2f\n", lKey, *lValue);
    }

    lMap->delete(&lMap);
}
//===============================================
static void GTest_runXmlNodeNamePrint(GTestO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GXmlO* lDom = GXml_new();

    lDom->loadXmlFile(lDom, "process.xml");
    lDom->getRoot(lDom, "rdv");
    GTest_runXmlNodeNamePrintChildren(lDom);
    lDom->delete(&lDom);
}
//===============================================
static void GTest_runXmlNodeNamePrintChildren(GXmlO* _obj) {
    GXmlO* lNode = GXml_new();
    GXmlO* lChildren = GXml_new();

    _obj->getNodePtr(_obj, lNode);

    while(1) {
        if(lNode->isNodeEmpty(lNode)) break;
        int lType = lNode->getNodeType(lNode);
        if(lType == XML_ELEMENT_NODE) {
            const char* lName = lNode->getNodeName(lNode);
            printf("<%s>\n", lName);
        }
        lNode->getNodeChildren(lNode, lChildren);
        GTest_runXmlNodeNamePrintChildren(lChildren);
        lNode->getNodeNext(lNode, lNode);
    }

    lNode->delete(&lNode);
    lChildren->delete(&lChildren);
}
//===============================================
