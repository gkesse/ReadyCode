//===============================================
#include "GList.h"
//===============================================
static void GList_delete(GObjectO* _obj);
static void GList_loadXmlFile(GObjectO* _obj, const char* _filename);
static void GList_loadXmlData(GObjectO* _obj, char* _source, int _size);
static GListO* GList_getRoot(GObjectO* _obj, const char* _nodename);
static GListO* GList_getNode(GObjectO* _obj, const char* _nodename);
static char* GList_getNodeName(GObjectO* _obj);
static char* GList_getNodeValue(GObjectO* _obj);
static int GList_countNode(GObjectO* _obj);
//===============================================
GObjectO* GList_New() {
    GObjectO* lParent = GObject_new();
    GListO* lChild = (GListO*)malloc(sizeof(GListO));

    lChild->loadXmlFile = GList_loadXmlFile;
    lChild->loadXmlData = GList_loadXmlData;
    lChild->getRoot = GList_getRoot;
    lChild->getNode = GList_getNode;
    lChild->getNodeName = GList_getNodeName;
    lChild->getNodeValue = GList_getNodeValue;
    lChild->countNode = GList_countNode;
    lChild->m_doc = 0;
    lChild->m_node = 0;

    lParent->child = lChild;
    lParent->delete = GList_delete;
    return lParent;
}
//===============================================
static void GList_delete(GObjectO* _obj) {
    GListO* lChild = _obj->child;
    xml_document_free(lChild->m_doc, false);
    GObject_delete(_obj);
}
//===============================================
static void GList_loadXmlFile(GObjectO* _obj, const char* _filename) {
    GListO* lChild = _obj->child;
    FILE* lFile = fopen(_obj->getXmlPath(_obj, _filename), "r");
    if(!lFile) {
        printf("Erreur la methode (GList_LoadXmlFile) a echoue "
                "sur le fichier (%s) (1).\n", _filename);
        return;
    }
    int lSize = _obj->fsize(_obj, lFile);
    char* lBuffer = (char*)malloc(sizeof(char)*(lSize + 1));
    int lBytes = fread(lBuffer, 1, lSize, lFile);
    if(lBytes <= 0) {
        printf("Erreur la methode (GList_LoadXmlFile) a echoue "
                "sur le fichier (%s) (2).\n", _filename);
        return;
    }
    lBuffer[lBytes] = 0;
    lChild->m_doc = xml_parse_document(lBuffer, lSize);
    if(!lChild->m_doc) {
        printf("Erreur la methode (GList_LoadXmlFile) a echoue "
                "sur le fichier (%s) (3).\n", _filename);
        return;
    }
    fclose(lFile);
}
//===============================================
static void GList_loadXmlData(GObjectO* _obj, char* _source, int _size) {
    GListO* lChild = _obj->child;
    lChild->m_doc = xml_parse_document(_source, _size);
    if(!lChild->m_doc) {
        printf("Erreur la methode (GList_loadXmlData) a echoue.");
        return;
    }
}
//===============================================
static GListO* GList_getRoot(GObjectO* _obj, const char* _nodename) {
    GListO* lChild = _obj->child;
    lChild->m_node = xml_document_root(lChild->m_doc);
    if(!lChild->m_node) {
        printf("Erreur la methode (GList_getRoot) a echoue "
                "sur le noeud (%s) (1).\n", _nodename);
        return lChild;
    }
    if(strcmp(_nodename, GList_getNodeName(_obj))) {
        printf("Erreur la methode (GList_getRoot) a echoue "
                "sur le noeud (%s) (2).\n", _nodename);
        lChild->m_node = 0;
        return lChild;
    }
    return lChild;
}
//===============================================
static GListO* GList_getNode(GObjectO* _obj, const char* _nodename) {
    GListO* lChild = _obj->child;
    if(!lChild->m_node) {
        printf("Erreur la methode (GList_getNode) a echoue "
                "sur le noeud (%s) (1).\n", _nodename);
        return lChild;
    }
    int lCount = xml_node_children(lChild->m_node);
    for(int i = 0; i < lCount; i++) {
        struct xml_node* lNode = xml_node_child(lChild->m_node, i);
        uint8_t* lNodeName = xml_easy_name(lNode);
        if(!strcmp(_nodename, lNodeName)) {
            free(lNodeName);
            lChild->m_node = lNode;
            return lChild;
        }
        free(lNodeName);
    }
    printf("Erreur la methode (GList_getNode) a echoue "
            "sur le noeud (%s) (2).\n", _nodename);
    lChild->m_node = 0;
    return lChild;
}
//===============================================
static char* GList_getNodeName(GObjectO* _obj) {
    GListO* lChild = _obj->child;
    uint8_t* lData = xml_easy_name(lChild->m_node);
    sprintf(lChild->m_nodeName, "%s", lData);
    free(lData);
    return lChild->m_nodeName;
}
//===============================================
static char* GList_getNodeValue(GObjectO* _obj) {
    GListO* lChild = _obj->child;
    uint8_t* lData = xml_easy_content(lChild->m_node);
    sprintf(lChild->m_nodeValue, "%s", lData);
    free(lData);
    return lChild->m_nodeValue;
}
//===============================================
static int GList_countNode(GObjectO* _obj) {
    GListO* lChild = _obj->child;
    int lCount = (int)xml_node_children(lChild->m_node);
    return lCount;
}
//===============================================
