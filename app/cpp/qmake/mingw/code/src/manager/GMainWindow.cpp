//===============================================
#include "GMainWindow.h"
#include "GLog.h"
#include "GCode.h"
#include "GPath.h"
//===============================================
GMainWindow::GMainWindow(QWidget* _parent)
: QMainWindow(_parent) {
}
//===============================================
GMainWindow::~GMainWindow() {

}
//===============================================
void GMainWindow::createDoms() {
    m_dom.reset(new GCode);
    m_dom->loadFile(GRES("xml", "app.xml"));
}
//===============================================
QString GMainWindow::getItem(const QString& _code, const QString& _key) const {
    return m_dom->getItem(_code, _key);
}
//===============================================
QString GMainWindow::getItem(const QString& _code, int _index) const {
    return m_dom->getItem(_code, _index);
}
//===============================================
QString GMainWindow::getItem(const QString& _code, const QString& _key, int _index) const {
    return m_dom->getItem(_code, _key, _index);
}
//===============================================
QString GMainWindow::getItem(const QString& _code, const QString& _category, const QString& _key) const {
    return m_dom->getItem(_code, _category, _key);
}
//===============================================
int GMainWindow::countItem(const QString& _code) const {
    return m_dom->countItem(_code);
}
//===============================================
void GMainWindow::addObj(const QString& _key, void* _obj) {
    m_objs[_key] = _obj;
}
//===============================================
void* GMainWindow::getObj(const QString& _key, void* _defaultValue) const {
    void* lObj = m_objs.value(_key, _defaultValue);
    return lObj;
}
//===============================================
QString GMainWindow::getKey(void* _obj, const QString& _defaultValue) const {
    QString lKey = m_objs.key(_obj, _defaultValue);
    return lKey;
}
//===============================================
void GMainWindow::onErrorKey(const QString& _key) {
    GERROR_ADD(eGERR, QString(""
            "Erreur la cle (%1) n'existe pas.\n"
            "").arg(_key)
    );
}
//===============================================
