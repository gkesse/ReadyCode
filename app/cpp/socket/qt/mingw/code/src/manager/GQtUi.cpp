//===============================================
#include "GQtUi.h"
#include "GQtWidget.h"
#include "GQt.h"
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
	GQt lQt; QString lKey;
    QApplication lApp(_argc, _argv);
    lQt.getKey(_argc, _argv, 2, lKey);
    GQtWidget* lWindow = GQtWidget::Create(lKey);
    lWindow->show();
    lApp.exec();
}
//===============================================
