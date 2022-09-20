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
void GXml2::setData(const GString2& _data) {
    m_data = _data;
}
//===============================================
void GXml2::setFilename(const GString2& _filename) {
    m_filename = _filename;
}
//===============================================
void GXml2::setPath(const GString2& _path) {
    m_path = _path;
}
//===============================================
bool GXml2::loadData() {
    if(m_data == "") return false;
    m_doc = xmlParseDoc(BAD_CAST(m_data.c_str()));
    if(!m_doc) {GERROR_ADD(eGERR, "Erreur lors de la création du document."); return false;}
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
bool GXml2::loadFile() {
    if(m_filename == "") return false;
    m_doc = xmlParseFile(m_filename.c_str());
    if(!m_doc) {GERROR_ADD(eGERR, "Erreur lors de la création du document."); return false;}
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
GString2 GXml2::getData() {
    GString2 lData;
    int lCount = m_path.count("/");
    for(int i = 0; i < lCount; i++) {
        GString2 lPath = m_path.extract(i, "/");
        lPath.print();
    }
    return lData;
}
//===============================================
