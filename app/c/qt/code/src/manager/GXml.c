//===============================================
#include "GXml.h"
//===============================================
static void GXml_delete(GObjectO* _obj);
static void GXml_loadXmlFile(GObjectO* _obj, const char* _filename);
static void GXml_loadXmlData(GObjectO* _obj, char* _source, int _size);
static GXmlO* GXml_getRoot(GObjectO* _obj, const char* _nodename);
static GXmlO* GXml_getNode(GObjectO* _obj, const char* _nodename);
static GXmlO* GXml_getNodeEmpty(GObjectO* _obj, const char* _nodename);
static GXmlO* GXml_getNodeIndex(GObjectO* _obj, const char* _nodename, int _index);
static char* GXml_getNodeName(GObjectO* _obj);
static char* GXml_getNodeValue(GObjectO* _obj);
static int GXml_countNode(GObjectO* _obj, const char* _nodename);
//===============================================
GObjectO* GXml_New() {
    GObjectO* lParent = GObject_new();
    GXmlO* lChild = (GXmlO*)malloc(sizeof(GXmlO));

    lChild->loadXmlFile = GXml_loadXmlFile;
    lChild->loadXmlData = GXml_loadXmlData;
    lChild->getRoot = GXml_getRoot;
    lChild->getNode = GXml_getNode;
    lChild->getNodeEmpty = GXml_getNodeEmpty;
    lChild->getNodeIndex = GXml_getNodeIndex;
    lChild->getNodeName = GXml_getNodeName;
    lChild->getNodeValue = GXml_getNodeValue;
    lChild->countNode = GXml_countNode;
    lChild->m_doc = 0;
    lChild->m_node = 0;

    lParent->child = lChild;
    lParent->delete = GXml_delete;
    return lParent;
}
//===============================================
static void GXml_delete(GObjectO* _obj) {
    GXmlO* lChild = _obj->child;
    xml_document_free(lChild->m_doc, false);
    GObject_delete(_obj);
}
//===============================================
static void GXml_loadXmlFile(GObjectO* _obj, const char* _filename) {
    GXmlO* lChild = _obj->child;
    FILE* lFile = fopen(_obj->getXmlPath(_obj, _filename), "r");
    if(!lFile) {
        printf("Erreur la methode (GXml_LoadXmlFile) a echoue "
                "sur le fichier (%s) (1).\n", _filename);
        return;
    }
    int lSize = _obj->fsize(_obj, lFile);
    char* lBuffer = (char*)malloc(sizeof(char)*(lSize + 1));
    int lBytes = fread(lBuffer, 1, lSize, lFile);
    if(lBytes <= 0) {
        printf("Erreur la methode (GXml_LoadXmlFile) a echoue "
                "sur le fichier (%s) (2).\n", _filename);
        return;
    }
    lBuffer[lBytes] = 0;
    lChild->m_doc = xml_parse_document(lBuffer, lSize);
    if(!lChild->m_doc) {
        printf("Erreur la methode (GXml_LoadXmlFile) a echoue "
                "sur le fichier (%s) (3).\n", _filename);
        return;
    }
    fclose(lFile);
}
//===============================================
static void GXml_loadXmlData(GObjectO* _obj, char* _source, int _size) {
    GXmlO* lChild = _obj->child;
    lChild->m_doc = xml_parse_document(_source, _size);
    if(!lChild->m_doc) {
        printf("Erreur la methode (GXml_loadXmlData) a echoue.");
        return;
    }
}
//===============================================
static GXmlO* GXml_getRoot(GObjectO* _obj, const char* _nodename) {
    GXmlO* lChild = _obj->child;
    lChild->m_node = xml_document_root(lChild->m_doc);
    if(!lChild->m_node) {
        printf("Erreur la methode (GXml_getRoot) a echoue "
                "sur le noeud (%s) (1).\n", _nodename);
        return lChild;
    }
    if(strcmp(_nodename, GXml_getNodeName(_obj))) {
        printf("Erreur la methode (GXml_getRoot) a echoue "
                "sur le noeud (%s) (2).\n", _nodename);
        lChild->m_node = 0;
        return lChild;
    }
    return lChild;
}
//===============================================
static GXmlO* GXml_getNode(GObjectO* _obj, const char* _nodename) {
    GXmlO* lChild = _obj->child;
    if(!lChild->m_node) {
        printf("Erreur la methode (GXml_getNode) a echoue "
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
    printf("Erreur la methode (GXml_getNode) a echoue "
            "sur le noeud (%s) (2).\n", _nodename);
    lChild->m_node = 0;
    return lChild;
}
//===============================================
static GXmlO* GXml_getNodeEmpty(GObjectO* _obj, const char* _nodename) {
    GXmlO* lChild = _obj->child;
    if(!lChild->m_node) {
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
    lChild->m_node = 0;
    return lChild;
}
//===============================================
static GXmlO* GXml_getNodeIndex(GObjectO* _obj, const char* _nodename, int _index) {
    GXmlO* lChild = _obj->child;
    if(!lChild->m_node) {
        return lChild;
    }
    int lCount = xml_node_children(lChild->m_node);
    for(int i = 0; i < lCount; i++) {
        struct xml_node* lNode = xml_node_child(lChild->m_node, i);
        uint8_t* lNodeName = xml_easy_name(lNode);
        if(!strcmp(_nodename, lNodeName)) {
            free(lNodeName);
            if(i == _index) {
                lChild->m_node = lNode;
                return lChild;
            }
        }
        free(lNodeName);
    }
    lChild->m_node = 0;
    return lChild;
}
//===============================================
static char* GXml_getNodeName(GObjectO* _obj) {
    GXmlO* lChild = _obj->child;
    if(!lChild->m_node) return "";
    uint8_t* lData = xml_easy_name(lChild->m_node);
    sprintf(lChild->m_nodeName, "%s", lData);
    free(lData);
    return lChild->m_nodeName;
}
//===============================================
static char* GXml_getNodeValue(GObjectO* _obj) {
    GXmlO* lChild = _obj->child;
    if(!lChild->m_node) return "";
    uint8_t* lData = xml_easy_content(lChild->m_node);
    sprintf(lChild->m_nodeValue, "%s", lData);
    free(lData);
    return lChild->m_nodeValue;
}
//===============================================
static int GXml_countNode(GObjectO* _obj, const char* _nodename) {
    GXmlO* lChild = _obj->child;
    if(!lChild->m_node) return 0;
    int lNodeCount = (int)xml_node_children(lChild->m_node);
    int lCount = 0;
    for(int i = 0; i < lNodeCount; i++) {
        struct xml_node* lNode = xml_node_child(lChild->m_node, i);
        uint8_t* lNodeName = xml_easy_name(lNode);
        if(!strcmp(_nodename, lNodeName)) {
            free(lNodeName);
            lCount++;
        }
        free(lNodeName);
    }
    return lCount;
}
//===============================================
