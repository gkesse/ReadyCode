//===============================================
#include "GQtWindow.h"
#include "GQtLog.h"
#include "GQt.h"
#include "GQtDialog.h"
#include "GQtSpreadWindow.h"
//===============================================
GQtWindow::GQtWindow(QWidget* _parent) :
GQtWidget(_parent) {
    sGQt lParams;

    m_GQtSpreadWindow = new GQtSpreadWindow;

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
    GQTLOG->showMsg(GMSG);
    m_GQtSpreadWindow->show();
}
//===============================================
