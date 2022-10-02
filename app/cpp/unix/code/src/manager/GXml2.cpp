//===============================================
#include "GXml2.h"
#include "GLog.h"
//===============================================
GXml2::GXml2()
: GObject2() {
    m_doc = 0;
    m_xpath = 0;
    m_xpathObj = 0;
    m_node = 0;
    m_next = 0;
    xmlKeepBlanksDefault(0);
}
//===============================================
GXml2::~GXml2() {
    release();
}
//===============================================
void GXml2::release() {
    if(m_xpathObj) {xmlXPathFreeObject(m_xpathObj); m_xpathObj = 0;}
    if(m_xpath) {xmlXPathFreeContext(m_xpath); m_xpath = 0;}
    if(m_doc) {xmlFreeDoc(m_doc); m_doc = 0;}
}
//===============================================
void GXml2::initModule() {
    xmlInitParser();
}
//===============================================
void GXml2::cleanModule() {
    xmlCleanupParser();
    xmlMemoryDump();
}
//===============================================
bool GXml2::loadXml(const GString& _xml) {
    GString lXml = _xml.trim();
    if(lXml == "") return false;
    m_doc = xmlParseDoc(BAD_CAST(lXml.c_str()));
    if(!m_doc) {GERROR_ADD(eGERR, "Erreur lors de la création du document."); return false;}
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
    m_node = xmlDocGetRootElement(m_doc);
    if(!m_node) {GERROR_ADD(eGERR, "Erreur lors de la lecture du noeud racine."); return false;}
    return true;
}
//===============================================
bool GXml2::loadFile(const GString& _filename) {
    if(_filename == "") return false;
    m_doc = xmlParseFile(_filename.c_str());
    if(!m_doc) {GERROR_ADD(eGERR, "Erreur lors de la création du document."); return false;}
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
    m_node = xmlDocGetRootElement(m_doc);
    if(!m_node) {GERROR_ADD(eGERR, "Erreur lors de la lecture du noeud racine."); return false;}
    return true;
}
//===============================================
bool GXml2::loadNode(const GString& _data) {
    if(_data.trim().isEmpty()) return false;
    if(!m_node) return false;
    xmlNodePtr lNewNode;
    xmlParseInNodeContext(m_node, _data.c_str(), _data.size(), 0, &lNewNode);
    xmlNodePtr lNode = lNewNode->children;
    while(lNode) {
        xmlAddChild(m_node, xmlCopyNode(lNode, 1));
        lNode = lNode->next;
    }
    xmlFreeNode(lNewNode);
    return true;
}
//===============================================
bool GXml2::createDoc() {
    m_doc = xmlNewDoc(BAD_CAST "1.0");
    if(!m_doc) {GERROR_ADD(eGERR, "Erreur lors de la création du document."); return false;}
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
bool GXml2::createNode(const GString& _name) {
    if(!m_node) {
        m_node = xmlNewNode(NULL, BAD_CAST(_name.c_str()));
        if(!m_node) {GERROR_ADD(eGERR, "Erreur lors de la création du noeud."); return false;}
        xmlDocSetRootElement(m_doc, m_node);
    }
    else {
        m_next = xmlNewNode(NULL, BAD_CAST(_name.c_str()));
        if(!m_next) {GERROR_ADD(eGERR, "Erreur lors de la création du noeud."); return false;}
        xmlAddChild(m_node, m_next);
    }
    return true;
}
//===============================================
bool GXml2::createNodePath(const GString& _path) {
    int lCount = _path.countSep("/");
    GString lPath = "";
    for(int i = 0; i < lCount; i++) {
        GString lItem = _path.extract(i, "/");
        if(lItem == "") continue;
        lPath += "/";
        lPath += lItem;
        if(!getNode(lPath)) {
            createNode(lItem);
            next();
        }
    }
    return true;
}
//===============================================
bool GXml2::next() {
    if(!m_next) return false;
    m_node = m_next;
    return true;
}
//===============================================
bool GXml2::getNode(const GString& _path) {
    if(!m_xpath) return false;
    m_xpathObj = xmlXPathEvalExpression(BAD_CAST(_path.c_str()), m_xpath);
    if(!m_xpathObj) return false;
    if(!m_xpathObj->nodesetval) {xmlXPathFreeObject(m_xpathObj); m_xpathObj = 0; return false;}
    if(!m_xpathObj->nodesetval->nodeNr) {xmlXPathFreeObject(m_xpathObj); m_xpathObj = 0; return false;}
    m_node = m_xpathObj->nodesetval->nodeTab[0];
    xmlXPathFreeObject(m_xpathObj);
    m_xpathObj = 0;
    return true;
}
//===============================================
GString GXml2::getValue() const {
    if(!m_node) return "";
    GString lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
bool GXml2::setValue(const GString& _value, bool _isCData) {
    if(!m_doc) return false;
    if(!m_node) return false;
    if(!_isCData) {
        xmlNodeSetContent(m_node, BAD_CAST(_value.c_str()));
    }
    else {
        xmlNodePtr lNode = xmlNewCDataBlock(m_doc, BAD_CAST(_value.c_str()), _value.size());
        if(!lNode) {GERROR_ADD(eGERR, "Erreur lors de la création du noeud."); return false;}
        xmlAddChild(m_node, lNode);
    }
    return true;
}
//===============================================
int GXml2::countNode(const GString& _path) {
    if(!m_xpath) return 0;
    m_xpathObj = xmlXPathEvalExpression(BAD_CAST(_path.c_str()), m_xpath);
    if(!m_xpathObj) return 0;
    if(!m_xpathObj->nodesetval) {xmlXPathFreeObject(m_xpathObj); m_xpathObj = 0; return 0;}
    int lCount = m_xpathObj->nodesetval->nodeNr;
    xmlXPathFreeObject(m_xpathObj);
    m_xpathObj = 0;
    return lCount;
}
//===============================================
GString GXml2::toString() const {
    if(!m_doc) return "";
    if(!m_node) return "";
    xmlChar* lBuffer = NULL;
    int lSize;
    xmlDocDumpFormatMemoryEnc(m_doc, &lBuffer, &lSize, "UTF-8", 4);
    GString lData = (char*)lBuffer;
    xmlFree(lBuffer);
    return lData;
}
//===============================================
GString GXml2::toNode() const {
    if(!m_node) return "";
    xmlBufferPtr lBuffer = xmlBufferCreate();
    xmlNodeDump(lBuffer, m_doc, m_node, 0, 1);
    GString lData = (char*)lBuffer->content;
    xmlBufferFree(lBuffer);
    return lData;
}
//===============================================
void GXml2::print() const {
    printf("%s\n", toString().c_str());
}
//===============================================
