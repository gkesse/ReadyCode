//===============================================
#include "GXmlParser.h"
//===============================================
static void GXmlParser_delete(GXmlParserO* _obj);
static void GXmlParser_run(GXmlParserO* _obj, int _argc, char** _argv);
static void GXmlParser_runTest(GXmlParserO* _obj, int _argc, char** _argv);
//===============================================
static void GXmlParser_loadXmlFile(GXmlParserO* _obj, const char* _filename);
static void GXmlParser_loadXmlData(GXmlParserO* _obj, char* _source, int _size);
static void GXmlParser_createDoc(GXmlParserO* _obj, const char* _root);
static GXmlParserO* GXmlParser_getRoot(GXmlParserO* _obj, const char* _nodename);
static GXmlParserO* GXmlParser_getNode(GXmlParserO* _obj, const char* _nodename);
static GXmlParserO* GXmlParser_getNodeEmpty(GXmlParserO* _obj, const char* _nodename);
static GXmlParserO* GXmlParser_getNodeIndex(GXmlParserO* _obj, const char* _nodename, int _index);
static char* GXmlParser_getNodeName(GXmlParserO* _obj);
static char* GXmlParser_getNodeValue(GXmlParserO* _obj);
static char* GXmlParser_getNodeXml(GXmlParserO* _obj);
static int GXmlParser_countNode(GXmlParserO* _obj, const char* _nodename);
//===============================================
GXmlParserO* GXmlParser_new() {
    GObjectO* lParent = GObject_new();
    GXmlParserO* lChild = (GXmlParserO*)malloc(sizeof(GXmlParserO));

    lChild->parent = lParent;
    lChild->delete = GXmlParser_delete;
    lChild->run = GXmlParser_run;
    //
    lChild->loadXmlFile = GXmlParser_loadXmlFile;
    lChild->loadXmlData = GXmlParser_loadXmlData;
    lChild->createDoc = GXmlParser_createDoc;
    lChild->getRoot = GXmlParser_getRoot;
    lChild->getNode = GXmlParser_getNode;
    lChild->getNodeEmpty = GXmlParser_getNodeEmpty;
    lChild->getNodeIndex = GXmlParser_getNodeIndex;
    lChild->getNodeName = GXmlParser_getNodeName;
    lChild->getNodeValue = GXmlParser_getNodeValue;
    lChild->getNodeXml = GXmlParser_getNodeXml;
    lChild->countNode = GXmlParser_countNode;
    lChild->m_doc = 0;
    lChild->m_node = 0;

    lParent->child = lChild;

    return lChild;
}
//===============================================
static void GXmlParser_delete(GXmlParserO* _obj) {
    if(_obj->m_doc) {
        xml_document_free(_obj->m_doc, false);
    }
    GObject_delete(_obj->parent);
}
//===============================================
static void GXmlParser_run(GXmlParserO* _obj, int _argc, char** _argv) {
    char* lKey = "default";
    //
    if(_argc > 2) {
        lKey = _argv[2];
    }
    //
    if(!strcmp(lKey, "test")) {
        GXmlParser_runTest(_obj, _argc, _argv);
    }
}
//===============================================
static void GXmlParser_runTest(GXmlParserO* _obj, int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
}
//===============================================
static void GXmlParser_loadXmlFile(GXmlParserO* _obj, const char* _filename) {
    GObjectO* lObj = _obj->parent;
    FILE* lFile = fopen(lObj->getRepoPath(lObj, "c/xml", _filename), "r");
    if(!lFile) {
        printf("Erreur la methode (GXmlParser_LoadXmlFile) a echoue "
                "sur le fichier (%s) (1).\n", _filename);
        return;
    }
    int lSize = lObj->fsize(lObj, lFile);
    char* lBuffer = (char*)malloc(sizeof(char)*(lSize + 1));
    int lBytes = fread(lBuffer, 1, lSize, lFile);
    if(lBytes <= 0) {
        printf("Erreur la methode (GXmlParser_LoadXmlFile) a echoue "
                "sur le fichier (%s) (2).\n", _filename);
        return;
    }
    lBuffer[lBytes] = 0;
    _obj->m_doc = xml_parse_document(lBuffer, lSize);
    if(!_obj->m_doc) {
        printf("Erreur la methode (GXmlParser_LoadXmlFile) a echoue "
                "sur le fichier (%s) (3).\n", _filename);
        return;
    }
    fclose(lFile);
}
//===============================================
static void GXmlParser_loadXmlData(GXmlParserO* _obj, char* _source, int _size) {
    _obj->m_doc = xml_parse_document(_source, _size);
    if(!_obj->m_doc) {
        printf("Erreur la methode (GXmlParser_loadXmlData) a echoue.");
        return;
    }
}
//===============================================
static void GXmlParser_createDoc(GXmlParserO* _obj, const char* _root) {
    char* lDoc = "<rdv></rdv>";
    _obj->loadXmlData(_obj, lDoc, strlen(lDoc));
}
//===============================================
static GXmlParserO* GXmlParser_getRoot(GXmlParserO* _obj, const char* _nodename) {
    _obj->m_node = xml_document_root(_obj->m_doc);
    if(!_obj->m_node) {
        printf("Erreur la methode (GXmlParser_getRoot) a echoue "
                "sur le noeud (%s) (1).\n", _nodename);
        return _obj;
    }
    if(strcmp(_nodename, GXmlParser_getNodeName(_obj))) {
        printf("Erreur la methode (GXmlParser_getRoot) a echoue "
                "sur le noeud (%s) (2).\n", _nodename);
        _obj->m_node = 0;
        return _obj;
    }
    return _obj;
}
//===============================================
static GXmlParserO* GXmlParser_getNode(GXmlParserO* _obj, const char* _nodename) {
    if(!_obj->m_node) {
        printf("Erreur la methode (GXmlParser_getNode) a echoue "
                "sur le noeud (%s) (1).\n", _nodename);
        return _obj;
    }
    int lCount = xml_node_children(_obj->m_node);
    for(int i = 0; i < lCount; i++) {
        struct xml_node* lNode = xml_node_child(_obj->m_node, i);
        uint8_t* lNodeName = xml_easy_name(lNode);
        if(!strcmp(_nodename, lNodeName)) {
            free(lNodeName);
            _obj->m_node = lNode;
            return _obj;
        }
        free(lNodeName);
    }
    printf("Erreur la methode (GXmlParser_getNode) a echoue "
            "sur le noeud (%s) (2).\n", _nodename);
    _obj->m_node = 0;
    return _obj;
}
//===============================================
static GXmlParserO* GXmlParser_getNodeEmpty(GXmlParserO* _obj, const char* _nodename) {
    if(!_obj->m_node) {
        return _obj;
    }
    int lCount = xml_node_children(_obj->m_node);
    for(int i = 0; i < lCount; i++) {
        struct xml_node* lNode = xml_node_child(_obj->m_node, i);
        uint8_t* lNodeName = xml_easy_name(lNode);
        if(!strcmp(_nodename, lNodeName)) {
            free(lNodeName);
            _obj->m_node = lNode;
            return _obj;
        }
        free(lNodeName);
    }
    _obj->m_node = 0;
    return _obj;
}
//===============================================
static GXmlParserO* GXmlParser_getNodeIndex(GXmlParserO* _obj, const char* _nodename, int _index) {
    if(!_obj->m_node) {
        return _obj;
    }
    int lCount = xml_node_children(_obj->m_node);
    for(int i = 0; i < lCount; i++) {
        struct xml_node* lNode = xml_node_child(_obj->m_node, i);
        uint8_t* lNodeName = xml_easy_name(lNode);
        if(!strcmp(_nodename, lNodeName)) {
            free(lNodeName);
            if(i == _index) {
                _obj->m_node = lNode;
                return _obj;
            }
        }
        free(lNodeName);
    }
    _obj->m_node = 0;
    return _obj;
}
//===============================================
static char* GXmlParser_getNodeName(GXmlParserO* _obj) {
    if(!_obj->m_node) return "";
    uint8_t* lData = xml_easy_name(_obj->m_node);
    if(!lData) return "";
    sprintf(_obj->m_nodeName, "%s", lData);
    free(lData);
    return _obj->m_nodeName;
}
//===============================================
static char* GXmlParser_getNodeValue(GXmlParserO* _obj) {
    if(!_obj->m_node) return "";
    uint8_t* lData = xml_easy_content(_obj->m_node);
    if(!lData) return "";
    sprintf(_obj->m_nodeValue, "%s", lData);
    free(lData);
    return _obj->m_nodeValue;
}
//===============================================
static char* GXmlParser_getNodeXml(GXmlParserO* _obj) {
    char* lName = GXmlParser_getNodeName(_obj);
    char* lValue = GXmlParser_getNodeValue(_obj);
    sprintf(_obj->m_nodeXml, "<%s>%s</%s>", lName, lValue, lName);
    return _obj->m_nodeXml;
}
//===============================================
static int GXmlParser_countNode(GXmlParserO* _obj, const char* _nodename) {
    if(!_obj->m_node) return 0;
    int lNodeCount = (int)xml_node_children(_obj->m_node);
    int lCount = 0;
    for(int i = 0; i < lNodeCount; i++) {
        struct xml_node* lNode = xml_node_child(_obj->m_node, i);
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
