//===============================================
#include "GWidget.h"
#include "GLog.h"
#include "GCode.h"
#include "GPath.h"
//===============================================
GWidget::GWidget(QWidget* _parent)
: QFrame(_parent) {

}
//===============================================
GWidget::~GWidget() {

}
//===============================================
void GWidget::createDoms() {
    m_dom.reset(new GCode);
    m_dom->loadFile(GRES("xml", "app.xml"));
}
//===============================================
QString GWidget::getItem(const QString& _code, const QString& _key) const {
    return m_dom->getItem(_code, _key);
}
//===============================================
QString GWidget::getItem(const QString& _code, int _index) const {
    return m_dom->getItem(_code, _index);
}
//===============================================
QString GWidget::getItem(const QString& _code, const QString& _key, int _index) const {
    return m_dom->getItem(_code, _key, _index);
}
//===============================================
QString GWidget::getItem(const QString& _code, const QString& _category, const QString& _key) const {
    return m_dom->getItem(_code, _category, _key);
}
//===============================================
int GWidget::countItem(const QString& _code) const {
    return m_dom->countItem(_code);
}
//===============================================
void GWidget::addObj(const QString& _key, void* _obj) {
    if(_key == "") return;
    m_objs[_key] = _obj;
}
//===============================================
void* GWidget::getObj(const QString& _key, void* _defaultValue) const {
    void* lObj = m_objs.value(_key, _defaultValue);
    return lObj;
}
//===============================================
QString GWidget::getKey(void* _obj, const QString& _defaultValue) const {
    QString lKey = m_objs.key(_obj, _defaultValue);
    return lKey;
}
//===============================================
void GWidget::onErrorKey(const QString& _key) {
    GERROR(eGERR, QString(""
            "Erreur la cle (%1) n'existe pas.\n"
            "").arg(_key)
    );
}
//===============================================
