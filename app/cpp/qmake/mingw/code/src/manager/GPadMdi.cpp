//===============================================
#include "GPadMdi.h"
#include "GStyle.h"
#include "GPath.h"
#include "GPicto.h"
//===============================================
GPadMdi::GPadMdi(QWidget* _parent) :
GMainWindow(_parent) {
    GSTYLE(GRES("css", "style.css"));
    createDoms();
    createLayout();
}
//===============================================
GPadMdi::~GPadMdi() {

}
//===============================================
void GPadMdi::createLayout() {
    int lCount = countItem("pad/mdi");
    QString lBgColor = getItem("pad/mdi", "bg_color");

    m_mdiArea = new QMdiArea;
    m_mdiArea->setBackground(QBrush(QColor(lBgColor)));
    m_mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QMenu* lMenu = 0;
    QToolBar* lToolBar = 0;

    for(int i = 0; i < lCount; i++) {
        QString lCategory = getItem("pad/mdi", "category", i);
        QString lText = getItem("pad/mdi", "text", i);
        QString lPicto = getItem("pad/mdi", "picto", i);
        QString lPictoColor = getItem("pad/mdi", "picto_color", i);
        QString lShortcut = getItem("pad/mdi", "shortcut", i);
        QString lStatus = getItem("pad/mdi", "status", i);
        bool lToolBarOn = (getItem("pad/mdi", "toolbar_on", i) == "1");
        //
        if(lCategory == "menu") {
            lMenu = menuBar()->addMenu(lText);
            if(lToolBarOn) {
                lToolBar = addToolBar(tr("File"));
            }
        }
        else if(lCategory == "submenu") {
            const QIcon lIcon = GPICTO(lPicto, lPictoColor);
            QAction* lAction = new QAction(this);
            lAction->setText(lText);
            lAction->setIcon(lIcon);
            lAction->setShortcut(QKeySequence(lShortcut));
            lAction->setStatusTip(lStatus);
            connect(lAction, SIGNAL(triggered(bool)), this, SLOT(onTriggered(bool)));
            lMenu->addAction(lAction);

            if(lToolBarOn) {
                lToolBar->addAction(lAction);
            }
        }
    }

    QTextEdit* lText = new QTextEdit;
    m_mdiArea->addSubWindow(lText);
    lText->show();

    connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(onSubWindowActivated(QMdiSubWindow*)));

    resize(500, 400);

    setCentralWidget(m_mdiArea);
}
//===============================================
void GPadMdi::onTriggered(bool _checked) {

}
//===============================================
void GPadMdi::onSubWindowActivated(QMdiSubWindow* _window) {

}
//===============================================
