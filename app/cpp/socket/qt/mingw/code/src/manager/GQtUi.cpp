//===============================================
#include "GQtUi.h"
#include "GWidget.h"
#include "GStruct.h"
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
	QApplication lApp(_argc, _argv);
	GWidget* lWindow = GWidget::Create("opengl/grid/params");
	lWindow->show();
	lApp.exec();
}
//===============================================
