//===============================================
#include "GMainWindow.h"
#include "GLog.h"
#include "GCode.h"
#include "GPath.h"
//===============================================
GMainWindow::GMainWindow(QWidget* _parent) :
QMainWindow(_parent) {

}
//===============================================
GMainWindow::~GMainWindow() {

}
//===============================================
void GMainWindow::createDoms() {
    m_dom.reset(new GCode);
    m_dom->loadXmlFile(GRES("xml", "app.xml"));
    m_dom->createXPath();
}
//===============================================
QString GMainWindow::getItem(const QString& _code, const QString& _key) const {
    return m_dom->getItem(_code, _key);
}
//===============================================
QString GMainWindow::getItem(const QString& _code, const QString& _key, int _index) const {
    return m_dom->getItem(_code, _key, _index);
}
//===============================================
int GMainWindow::countItem(const QString& _code) const {
    return m_dom->countItem(_code);
}
//===============================================
void GMainWindow::addObject(QObject* _object, const QString& _key) {
	if(_key != "") {
		m_objectMap[_object] = _key;
	}
}
//===============================================
QObject* GMainWindow::getObject(const QString& _key) {
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
QString GMainWindow::getObject(QObject* _key, const QString& _defaultValue) {
    return m_objectMap.value(_key, _defaultValue);
}
//===============================================
