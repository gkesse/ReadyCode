//===============================================
#include <GFile.h>
#include <GXml.h>
//===============================================
GXml::GXml() {

}
//===============================================
GXml::~GXml() {

}
//===============================================
void GXml::load(const QString& _filename) {
    GFile lFile;
    lFile.openRead(_filename);
    m_document.setContent(&lFile.file(), true);
    lFile.close();
}
//===============================================
void GXml::save(const QString& _filename, int _indent) {
    GFile lFile;
    lFile.openWrite(_filename);
    QTextStream lOut(&lFile.file());
    m_document.save(lOut, _indent);
    lFile.close();
}
//===============================================
void GXml::content(const QString& _content) {
    m_document.setContent(_content);
}
//===============================================
void GXml::toString(QString& _content) {
    _content = m_document.toString(-1);
}
//===============================================
void GXml::toText(QString& _content) {
    QTextStream lTextStream(&_content);
    m_element.save(lTextStream, -1);
}
//===============================================
void GXml::value(const QString& _value) {
    m_element.setNodeValue(_value);
}
//===============================================
void GXml::element(GXml& _xml, const QString& _name) {
    _xml.m_element = m_document.createElement(_name);
}
//===============================================
void GXml::elements(GXml& _xml, const QString& _name) {
    _xml.m_nodes = m_document.elementsByTagName(_name);
}
//===============================================
void GXml::element(GXml& _xml, int _index) {
    _xml.m_element = m_nodes.at(_index).toElement();
}
//===============================================
void GXml::root(GXml& _root) {
    _root.m_element = m_document.documentElement();
}
//===============================================
void GXml::tagName(QString& _tagName) {
    _tagName = m_element.tagName();
}
//===============================================
bool GXml::attribute(const QString& _attribute) {
    return m_element.hasAttribute(_attribute);
}
//===============================================
void GXml::attribute(const QString& _attribute, QString& _value) {
    _value = m_element.attribute(_attribute);
}
//===============================================
void GXml::attributes(const QString& _attribute, const QString& _value) {
    m_element.setAttribute(_attribute, _value);
}
//===============================================
void GXml::firstChild(GXml& _xml, const QString& _tagName) {
    _xml.m_element = m_element.firstChildElement(_tagName);
}
//===============================================
void GXml::nextSibling(GXml& _xml, const QString& _tagName) {
    _xml.m_element = m_element.nextSiblingElement(_tagName);
}
//===============================================
void GXml::previousSibling(GXml& _xml, const QString& _tagName) {
    _xml.m_element = m_element.previousSiblingElement(_tagName);
}
//===============================================
void GXml::text(QString& _text) {
    _text = m_element.text();
}
//===============================================
void GXml::text(GXml& _xml, const QString& _text) {
    _xml.m_text = m_document.createTextNode(_text);
}
//===============================================
void GXml::appendChild(const GXml& _chlid) {
    m_element.appendChild(_chlid.m_element);
}
//===============================================
void GXml::replaceChild(const GXml& _old, const GXml& _new) {
    m_element.replaceChild(_new.m_element, _old.m_element);
}
//===============================================
bool GXml::isNull() {
    return m_element.isNull();
}
//===============================================
