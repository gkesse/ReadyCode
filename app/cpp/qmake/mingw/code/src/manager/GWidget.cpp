//===============================================
#include "GWidget.h"
#include "GLog.h"
#include "GXml.h"
//===============================================
GWidget::GWidget(QWidget* _parent) :
QFrame(_parent) {

}
//===============================================
GWidget::~GWidget() {

}
//===============================================
QString GWidget::getItem(const QString& _code, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='%1']/%2").arg(_code).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GWidget::getItem(const QString& _code, const QString& _data, int _i) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='%1']/map/data[position()=%2]/%3").arg(_code).arg(_i + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GWidget::countItem(const QString& _code) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='%1']/map/data").arg(_code));
    int lData = m_dom->countXPath();
    return lData;
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
        GLOGI->addError(QString("Erreur la methode (getKeyObject) a echoue\n"
                "sur la cle (%1).").arg(_key));
        GLOGI->showError(this);
    }
    return lObject;
}
//===============================================
