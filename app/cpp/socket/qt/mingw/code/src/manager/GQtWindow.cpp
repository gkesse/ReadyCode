//===============================================
#include "GQtWindow.h"
#include "GQt.h"
#include "GQtDialog.h"
//===============================================
GQtWindow::GQtWindow(QWidget* _parent) :
GQtWidget(_parent) {
    sGQt lParams;
    GQt lButton, lMainLayout;

    lButton.createQPushButton("Ouvrir");
    lMainLayout.createQVBoxLayout();
    lMainLayout.addWidget(lButton);
    lMainLayout.setAlignment(Qt::AlignTop | Qt::AlignRight);
    lMainLayout.setLayout(this);
    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);
    lButton.connectObject(SIGNAL(clicked()), this, SLOT(onOpenButton()));
}
//===============================================
GQtWindow::~GQtWindow() {

}
//===============================================
void GQtWindow::onOpenButton() {
    GQtDialog* lDialog = GQtDialog::Create("qt/cell/location");
    lDialog->exec();
    delete lDialog;
}
//===============================================
