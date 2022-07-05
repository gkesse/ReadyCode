//===============================================
#include "GObject.h"
#include "GLog.h"
#include "GCode.h"
#include "GPath.h"
//===============================================
GObject::GObject(QObject* _parent) : QObject(_parent) {

}
//===============================================
GObject::~GObject() {

}
//===============================================
void GObject::createDoms() {
    m_dom.reset(new GCode);
    m_dom->loadXmlFile(GRES("xml", "app.xml"));
    m_dom->createXPath();
}
//===============================================
QString GObject::getItem(const QString& _code, const QString& _key) const {
    return m_dom->getItem(_code, _key);
}
//===============================================
QString GObject::getItem(const QString& _code, int _index, bool _isCData) const {
    return m_dom->getItem(_code, _index, _isCData);
}
//===============================================
int GObject::countItem(const QString& _code) const {
    return m_dom->countItem(_code);
}
//===============================================
QSharedPointer<GError>& GObject::getErrors() {
    return m_errors;
}
//===============================================
void GObject::runDefault(int _argc, char** _argv) {
    GERROR(eGERR, "Vous devez selectionner un module.");
}
//===============================================
