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
    xmlXPathFreeObject(m_xpathObj);
    xmlXPathFreeContext(m_xpath);
    xmlFreeDoc(m_doc);
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
void GXml2::createNode(const GString2& _name) {
    if(!m_node) {
        m_node = xmlNewNode(NULL, BAD_CAST(_name.c_str()));
        xmlDocSetRootElement(m_doc, m_node);
    }
    else {
        m_next = xmlNewNode(NULL, BAD_CAST(_name.c_str()));
        xmlAddChild(m_node, m_next);
    }
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
