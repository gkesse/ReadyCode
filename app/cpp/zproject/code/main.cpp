//===============================================
#include "GInclude.h"
//===============================================
int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QWidget* lWindow = new QWidget;
    lWindow->setWindowTitle("ReadyApp");
    lWindow->resize(400, 200);
    lWindow->show();
    return app.exec();
}
//===============================================
