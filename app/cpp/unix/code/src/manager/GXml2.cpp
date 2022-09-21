//===============================================
#include "GXml2.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GXml2::GXml2()
: GObject() {
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
bool GXml2::loadXml(const GString2& _xml) {
    GString2 lXml = _xml.trim();
    if(lXml == "") return false;
    m_doc = xmlParseDoc(BAD_CAST(lXml.c_str()));
    if(!m_doc) {GERROR_ADD(eGERR, "Erreur lors de la création du document."); return false;}
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
bool GXml2::loadFile(const GString2& _filename) {
    if(_filename == "") return false;
    m_doc = xmlParseFile(_filename.c_str());
    if(!m_doc) {GERROR_ADD(eGERR, "Erreur lors de la création du document."); return false;}
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
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
bool GXml2::createNode(const GString2& _name) {
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
bool GXml2::createNodePath(const GString2& _path) {
    int lCount = _path.count("/");
    GString2 lPath = "";
    for(int i = 0; i < lCount; i++) {
        GString2 lItem = _path.extract(i, "/");
        if(lItem == "") continue;
        lPath += "/";
        lPath += lItem;
        createNode(lItem);
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
bool GXml2::getNode(const GString2& _path) {
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
bool GXml2::setValue(const GString2& _value, bool _isCData) {
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
GString2 GXml2::toString() const {
    if(!m_doc) return "";
    xmlChar* lBuffer = NULL;
    int lSize;
    xmlDocDumpFormatMemoryEnc(m_doc, &lBuffer, &lSize, "UTF-8", 4);
    GString2 lData = (char*)lBuffer;
    xmlFree(lBuffer);
    return lData;
}
//===============================================
