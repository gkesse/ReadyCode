//===============================================
#include "GWindow.h"
#include "GSQLite.h"
//===============================================
int main(int argc, char** argv) {
    QApplication app(argc, argv);
    GSQLite::Instance();
    GSQLite::Instance();
    GWindow* lWindow = new GWindow;    
    lWindow->setWindowTitle("ReadyApp");
    lWindow->resize(400, 10);
    lWindow->show();
    return app.exec();
}
//===============================================