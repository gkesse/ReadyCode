//===============================================
#include "GWidget.h"
#include "GLog.h"
//===============================================
GWidget::GWidget(QWidget* _parent) :
QFrame(_parent) {

}
//===============================================
GWidget::~GWidget() {

}
//===============================================
QObject* GWidget::getObject(const QString& _key) {
    QObject* lObject = m_objectMap.key(_key, 0);
    if(lObject == 0) {
        GLOG->addError(QString("Erreur la methode (getKeyObject) a echoue\n"
                "sur la cle (%1).").arg(_key));
        GLOG->showError(this);
    }
    return lObject;
}
//===============================================
