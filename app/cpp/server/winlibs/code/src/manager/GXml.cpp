//===============================================
#include "GXml.h"
//===============================================
GXml::GXml() {
    m_doc = 0;
    m_node = 0;
}
//===============================================
GXml::~GXml() {
    xmlFreeDoc(m_doc);
}
//===============================================
void GXml::createDoc() {
    m_doc = xmlNewDoc(BAD_CAST("1.0"));
    m_node = xmlNewNode(NULL, BAD_CAST("rdv"));
    xmlDocSetRootElement(m_doc, m_node);
}
//===============================================
xmlNodePtr GXml::addObj(const GString& _name) {
    xmlNodePtr lNode = xmlNewNode(NULL, BAD_CAST(_name.c_str()));
    xmlAddChild(m_node, lNode);
    return lNode;
}
//===============================================
void GXml::addData(const GString& _name, const GString& _value) {
    xmlNodePtr lNode = xmlNewNode(NULL, BAD_CAST(_name.c_str()));
    xmlNodeSetContent(lNode, BAD_CAST(_value.c_str()));
    xmlAddChild(m_node, lNode);
}
//===============================================
GString GXml::toString() const {
    xmlChar* lBuffer = NULL;
    int lSize;
    xmlDocDumpFormatMemoryEnc(m_doc, &lBuffer, &lSize, "UTF-8", 4);
    GString lData((char*)lBuffer, lSize);
    xmlFree(lBuffer);
    return lData;
}
//===============================================
