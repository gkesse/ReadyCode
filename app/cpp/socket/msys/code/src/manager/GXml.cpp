//===============================================
#include "GXml.h"
//===============================================
GXml::GXml() {
    m_node = 0;
    m_doc = 0;
}
//===============================================
GXml::~GXml() {

}
//===============================================
void GXml::free() {
    if(m_doc) {xmlFreeDoc(m_doc); m_doc = 0;}
    else if(m_node) {xmlFreeNode(m_node); m_node = 0;}
}
//===============================================
void GXml::filename(const std::string& filename) {
    m_filename = filename;
}
//===============================================
void GXml::blank() {
    xmlKeepBlanksDefault(0);
}
//===============================================
void GXml::parse() {
    m_doc = xmlParseFile(m_filename.c_str());
}
//===============================================
void GXml::root() {
    m_node = xmlDocGetRootElement(m_doc);
}
//===============================================
void GXml::node(const std::string& _node) {
    m_node = xmlNewNode(NULL, BAD_CAST(_node.c_str()));
}
//===============================================
void GXml::attribute(const std::string& _key, const std::string& _value) {
    xmlSetProp(m_node, BAD_CAST(_key.c_str()), BAD_CAST(_value.c_str()));
}
//===============================================
void GXml::data(const std::string& _data) {
    xmlNodeSetContent(m_node, BAD_CAST(_data.c_str()));
}
//===============================================
void GXml::child(GXml& _child) {
    xmlAddChild(m_node, _child.m_node);
}
//===============================================
void GXml::child(const std::string& _key, const std::string& _value) {
    xmlNewTextChild(m_node, NULL, BAD_CAST(_key.c_str()), BAD_CAST(_value.c_str()));
}
//===============================================
void GXml::nextSibling(GXml& _child) {
    xmlAddNextSibling(m_node, _child.m_node);
}
//===============================================
void GXml::prevSibling(GXml& _child) {
    xmlAddPrevSibling(m_node, _child.m_node);
}
//===============================================
void GXml::append(GXml& _child) {
    xmlAddSibling(m_node, _child.m_node);
}
//===============================================
void GXml::xpath(GXml& _xml, const std::string& _xpath) {
    xmlXPathInit();
    xmlXPathContextPtr lContext = xmlXPathNewContext(_xml.m_doc);
    xmlXPathObjectPtr lResult = xmlXPathEvalExpression(BAD_CAST(_xpath.c_str()), lContext);
    if(lResult && XPATH_NODESET == lResult->type && lResult->nodesetval->nodeNr == 1) {
        m_node = lResult->nodesetval->nodeTab[0];
    }
    xmlXPathFreeObject(lResult);
    xmlXPathFreeContext(lContext);
}
//===============================================
void GXml::print() const {
    xmlDocFormatDump(stdout, m_doc, 1);
}
//===============================================
void GXml::print(GXml& _xml) const {
    xmlBufferPtr lBuffer = xmlBufferCreate();
    int lSize = xmlNodeDump(lBuffer, _xml.m_doc, m_node, 0, 1);
    printf("%s\n", (char*)lBuffer->content);
    xmlBufferFree(lBuffer);
}
//===============================================
void GXml::create(const std::string& _reference, const std::string& _name, const std::string& _price) {
    node("product");
    attribute("reference", _reference);

    GXml lName;
    lName.node("name");
    lName.data(_name);

    child(lName);
    child("price", _price);
}
//===============================================
