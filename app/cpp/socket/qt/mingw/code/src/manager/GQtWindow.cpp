//===============================================
#include "GQtWindow.h"
#include "GLog.h"
#include "GQt.h"
#include "GQtDialog.h"
#include "GQtMainWindow.h"
//===============================================
GQtWindow::GQtWindow(QWidget* _parent) :
GQtWidget(_parent) {
    sGQt lParams;

    QPushButton* lButton = new QPushButton("Ouvrir");
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(lButton);
    lMainLayout->setAlignment(Qt::AlignTop | Qt::AlignRight);

    setLayout(lMainLayout);
    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);

    connect(lButton, SIGNAL(clicked()), this, SLOT(onOpenButton()));
}
//===============================================
GQtWindow::~GQtWindow() {

}
//===============================================
void GQtWindow::onOpenButton() {
    GLOG->log(GMSG);
    GQtMainWindow* lWindow = GQtMainWindow::Create("page/spreadsheet");
    lWindow->show();
}
//===============================================
