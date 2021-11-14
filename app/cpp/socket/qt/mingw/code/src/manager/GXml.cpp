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
void GXml::blank() {
    xmlKeepBlanksDefault(0);
}
//===============================================
void GXml::parse(const std::string& _filename) {
    m_doc = xmlParseFile(_filename.c_str());
}
//===============================================
void GXml::doc(const std::string& _version) {
    m_doc = xmlNewDoc(BAD_CAST(_version.c_str()));
}
//===============================================
void GXml::encoding(const std::string& _encoding) {
    xmlSaveFormatFileEnc("-", m_doc, _encoding.c_str(), 1);
}
//===============================================
void GXml::root() {
    m_node = xmlDocGetRootElement(m_doc);
}
//===============================================
void GXml::root(const std::string& _name) {
    m_node = xmlNewNode(NULL, BAD_CAST(_name.c_str()));
    xmlDocSetRootElement(m_doc, m_node);
}
//===============================================
void GXml::node(const std::string& _node) {
    m_node = xmlNewNode(NULL, BAD_CAST(_node.c_str()));
}
//===============================================
void GXml::attribute(const std::string& _key, const std::string& _value) {
    xmlNewProp(m_node, BAD_CAST(_key.c_str()), BAD_CAST(_value.c_str()));
}
//===============================================
void GXml::attributes(const std::string& _key, const std::string& _value) {
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
void GXml::child(GXml& _child, const std::string& _key) {
	_child.m_node = xmlNewChild(m_node, NULL, BAD_CAST(_key.c_str()), NULL);
}
//===============================================
void GXml::child(GXml& _child, const std::string& _key, const std::string& _value) {
	_child.m_node = xmlNewChild(m_node, NULL, BAD_CAST(_key.c_str()), BAD_CAST(_value.c_str()));
}
//===============================================
void GXml::content(const std::string& _value) {
    xmlNodeAddContent(m_node, BAD_CAST(_value.c_str()));
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
void GXml::toString(GXml& _xml, std::string& _data) {
    xmlBufferPtr lBuffer = xmlBufferCreate();
    xmlNodeDump(lBuffer, _xml.m_doc, m_node, 0, 1);
    _data = (char*)lBuffer->content;
    xmlBufferFree(lBuffer);
}
//===============================================
void GXml::print() const {
    xmlDocFormatDump(stdout, m_doc, 1);
}
//===============================================
void GXml::print(GXml& _xml) const {
    xmlBufferPtr lBuffer = xmlBufferCreate();
    xmlNodeDump(lBuffer, _xml.m_doc, m_node, 0, 1);
    printf("%s\n", (char*)lBuffer->content);
    xmlBufferFree(lBuffer);
}
//===============================================
