//===============================================
#include "GQFile.h"
#include "GQXml.h"
//===============================================
GQXml::GQXml() {

}
//===============================================
GQXml::~GQXml() {

}
//===============================================
void GQXml::load(const QString& _filename) {
    QString lErrorStr;
    int lErrorLine;
    int lErrorColumn;
    GQFile lFile;
    lFile.openRead(_filename);
	m_document.setContent(&lFile.file(), true, &lErrorStr, &lErrorLine, &lErrorColumn);
	lFile.close();
}
//===============================================
void GQXml::save(const QString& _filename, int _indent) {
	GQFile lFile;
    lFile.openWrite(_filename);
    QTextStream lOut(&lFile.file());
    m_document.save(lOut, _indent);
}
//===============================================
void GQXml::element(GQXml& _xml, const QString& _element) {
	_xml.m_element = m_document.createElement(_element);
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
void GQXml::appendChild(const GQXml& _chlid) {
    m_element.appendChild(_chlid.m_element);
}
//===============================================
void GQXml::replaceChild(const GQXml& _old, const GQXml& _new) {
    m_element.replaceChild(_new.m_element, _old.m_element);
}
//===============================================
bool GQXml::isNull() {
	return m_element.isNull();
}
//===============================================
