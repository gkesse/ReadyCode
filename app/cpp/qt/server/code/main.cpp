//===============================================
#include "GWindow.h"
//===============================================
int main(int argc, char** argv) {
    QApplication app(argc, argv);

    GWindow* lWindow = new GWindow;
    lWindow->setWindowTitle("ReadyApp");
    lWindow->resize(500, 300);
    lWindow->show();   
    
    return app.exec();
}
//===============================================