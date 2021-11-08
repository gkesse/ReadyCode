//===============================================
#include <GQXml.h>
//===============================================
GQXml::GQXml() {

}
//===============================================
GQXml::~GQXml() {

}
//===============================================
void GQXml::fileRead(const QString& _filename) {
	m_file.setFileName(_filename);
	m_file.open(QFile::ReadOnly | QFile::Text);
}
//===============================================
void GQXml::fileWrite(const QString& _filename) {
	m_file.setFileName(_filename);
	m_file.open(QFile::WriteOnly | QFile::Text);
}
//===============================================
void GQXml::save(int _indent) {
    QTextStream lOut(&m_file);
    m_document.save(lOut, _indent);
}
//===============================================
void GQXml::element(GQXml& _xml, const QString& _element) {
	_xml.m_element = m_document.createElement(_element);
}
//===============================================
void GQXml::content() {
    QString lErrorStr;
    int lErrorLine;
    int lErrorColumn;
	m_document.setContent(&m_file, true, &lErrorStr, &lErrorLine, &lErrorColumn);
}
//===============================================
void GQXml::root(GQXml& _root) {
	_root.m_element = m_document.documentElement();
}
//===============================================
void GQXml::tagName(QString& _tagName) {
    _tagName = m_element.tagName();
}
//===============================================
bool GQXml::attribute(const QString& _attribute) {
	return m_element.hasAttribute(_attribute);
}
//===============================================
void GQXml::attribute(const QString& _attribute, QString& _value) {
	_value = m_element.attribute(_attribute);
}
//===============================================
void GQXml::firstChild(GQXml& _xml, const QString& _tagName) {
	_xml.m_element = m_element.firstChildElement(_tagName);
}
//===============================================
void GQXml::nextSibling(GQXml& _xml, const QString& _tagName) {
	_xml.m_element = m_element.nextSiblingElement(_tagName);
}
//===============================================
void GQXml::text(QString& _text) {
	_text = m_element.text();
}
//===============================================
void GQXml::text(GQXml& _xml, QString& _text) {
    _xml.m_text = m_document.createTextNode(_text);
}
//===============================================
bool GQXml::isNull() {
	return m_element.isNull();
}
//===============================================
void GQXml::close() {
    m_file.close();
}
//===============================================
