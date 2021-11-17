//===============================================
#include "GQtUi.h"
#include "GWidget.h"
#include "GManager.h"
//===============================================
GQtUi::GQtUi() {

}
//===============================================
GQtUi::~GQtUi() {

}
//===============================================
GQtUi* GQtUi::Create(const QString& _key) {
    if(_key == "default") {return new GQtUi;}
    return new GQtUi;
}
//===============================================
void GQtUi::run(int _argc, char** _argv) {
	GManager lMgr; QString lKey;
    QApplication lApp(_argc, _argv);
	lMgr.getKey(_argc, _argv, 2, lKey);
    GWidget* lWindow = GWidget::Create(lKey);
    lWindow->show();
    lApp.exec();
}
//===============================================
