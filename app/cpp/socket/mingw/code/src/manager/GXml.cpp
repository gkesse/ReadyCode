//===============================================
#include "GXml.h"
//===============================================
GXml::GXml() {

}
//===============================================
GXml::~GXml() {

}
//===============================================
GXml& GXml::loadFile(const std::string& _filename) {
    m_result = m_doc.load_file(_filename.c_str());
    return *this;
}
//===============================================
GXml& GXml::parseData(const std::string& _xml) {
    m_result = m_doc.load_string(_xml.c_str());
    return *this;
}
//===============================================
GXml& GXml::createDoc() {
	m_node = m_doc.append_child(pugi::node_declaration);
    return *this;
}
//===============================================
GXml& GXml::addVersion(const std::string& _version) {
	m_node.append_attribute("version").set_value(_version.c_str());
    return *this;
}
//===============================================
GXml& GXml::addEncoding(const std::string& _encoding) {
	m_node.append_attribute("encoding").set_value(_encoding.c_str());
    return *this;
}
//===============================================
GXml& GXml::addStandalone(const std::string& _standalone) {
	m_node.append_attribute("standalone").set_value(_standalone.c_str());
    return *this;
}
//===============================================
GXml& GXml::addDocNode(GXml& _doc) {
	m_node.append_copy(_doc.m_doc.document_element());
    return *this;
}
//===============================================
GXml& GXml::docToString(std::string& _data) {
	std::stringstream lStream;
    m_doc.save(lStream, "   ", pugi::format_indent, pugi::encoding_utf8);
	_data = lStream;
    return *this;
}
//===============================================
GXml& GXml::createRoot(const std::string& _name) {
    m_node = m_doc.append_child(_name.c_str());
    return *this;
}
//===============================================
GXml& GXml::getRoot() {
    m_node = m_doc.document_element();
    return *this;
}
//===============================================
GXml& GXml::appendChild(GXml& _child, const std::string& _name) {
    _child.m_node = m_node.append_child(_name.c_str());
    return *this;
}
//===============================================
GXml& GXml::appendAttribute(const std::string& _name, const std::string& _value) {
    m_node.append_attribute(_name.c_str()).set_value(_value.c_str());
    return *this;
}
//===============================================
GXml& GXml::setNodeValue(const std::string& _value) {
    m_node.append_child(pugi::node_pcdata).set_value(_value.c_str());
    return *this;
}
//===============================================
GXml& GXml::getNodeValue(std::string& _value) {
    _value = m_node.value();
    return *this;
}
//===============================================
GXml& GXml::nodeIsNull(bool& _isNull) {
    _isNull = (m_node == 0);
    return *this;
}
//===============================================
GXml& GXml::firstChild(GXml& _child) {
    _child.m_node = m_node.first_child();
    return *this;
}
//===============================================
GXml& GXml::lastChild(GXml& _child) {
    _child.m_node = m_node.last_child();
    return *this;
}
//===============================================
GXml& GXml::nextSibling(GXml& _child) {
    _child.m_node = m_node.next_sibling();
    return *this;
}
//===============================================
GXml& GXml::prevSibling(GXml& _child) {
    _child.m_node = m_node.previous_sibling();
    return *this;
}
//===============================================
GXml& GXml::attributeIsNull(bool& _isNull) {
    _isNull = (m_attribute == 0);
    return *this;
}
//===============================================
GXml& GXml::firstAttribute(GXml& _child) {
    _child.m_attribute = m_node.first_attribute();
    return *this;
}
//===============================================
GXml& GXml::lastAttribute(GXml& _child) {
    _child.m_attribute = m_node.last_attribute();
    return *this;
}
//===============================================
GXml& GXml::nextAttribute(GXml& _child) {
    _child.m_attribute = m_attribute.next_attribute();
    return *this;
}
//===============================================
GXml& GXml::prevAttribute(GXml& _child) {
    _child.m_attribute = m_attribute.previous_attribute();
    return *this;
}
//===============================================
GXml& GXml::saveFile(const std::string& _filename) {
    m_doc.save_file(_filename.c_str(), "   ", pugi::format_indent, pugi::encoding_utf8);
    return *this;
}
//===============================================
GXml& GXml::printDoc() {
    m_doc.save(std::cout, "   ", pugi::format_indent, pugi::encoding_utf8);
    return *this;
}
//===============================================
