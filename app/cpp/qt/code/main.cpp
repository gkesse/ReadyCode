//===============================================
#include "GWindow.h"
//===============================================
int main(int argc, char** argv) {
    QApplication app(argc, argv);

    GWindow* lWindow = new GWindow;
    lWindow->setWindowTitle("ReadyApp");
    lWindow->resize(300, 200);
    lWindow->show();

    return app.exec();
}
//===============================================