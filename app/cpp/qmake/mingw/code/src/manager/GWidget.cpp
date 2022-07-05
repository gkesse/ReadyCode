//===============================================
#include "GWidget.h"
#include "GLog.h"
#include "GCode.h"
#include "GPath.h"
//===============================================
GWidget::GWidget(QWidget* _parent) :
QFrame(_parent) {

}
//===============================================
GWidget::~GWidget() {

}
//===============================================
void GWidget::createDoms() {
    m_dom.reset(new GCode);
    m_dom->loadXmlFile(GRES("xml", "app.xml"));
    m_dom->createXPath();
}
//===============================================
QString GWidget::getItem(const QString& _code, const QString& _key) const {
    return m_dom->getItem(_code, _key);
}
//===============================================
QString GWidget::getItem(const QString& _code, const QString& _key, int _index) const {
    return m_dom->getItem(_code, _key, _index);
}
//===============================================
QString GWidget::getItem(const QString& _code, const QString& _category, const QString& _key, bool _isCData) {
    return m_dom->getItem(_code, _category, _key, _isCData);
}
//===============================================
int GWidget::countItem(const QString& _code) const {
    return m_dom->countItem(_code);
}
//===============================================
void GWidget::addObject(QObject* _object, const QString& _key) {
	if(_key != "") {
		m_objectMap[_object] = _key;
	}
}
//===============================================
QObject* GWidget::getObject(const QString& _key) {
    QObject* lObject = m_objectMap.key(_key, 0);
    if(lObject == 0) {
        GERROR(eGERR, QString(""
                "Erreur la cle n'existe pas.\n"
                "cle..........: (%1)\n"
                "").arg(_key));
    }
    GERROR_SHOWG(eGERR);
    return lObject;
}
//===============================================
QString GWidget::getObject(QObject* _key, const QString& _defaultValue) {
    return m_objectMap.value(_key, _defaultValue);
}
//===============================================
