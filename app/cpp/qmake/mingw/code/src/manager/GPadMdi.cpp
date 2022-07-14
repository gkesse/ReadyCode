//===============================================
#include "GPadMdi.h"
#include "GLoginUi.h"
#include "GCvUi.h"
#include "GStyle.h"
#include "GPath.h"
#include "GPicto.h"
#include "GLog.h"
//===============================================
GPadMdi::GPadMdi(QWidget* _parent)
: GMainWindow(_parent) {
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
        QString lKey = getItem("pad/mdi", "key", i);
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
            connect(lMenu, SIGNAL(triggered(QAction*)), this, SLOT(onEvent(QAction*)));
        }
        else if(lCategory == "submenu") {
            const QIcon lIcon = GPICTO(lPicto, lPictoColor);
            QAction* lAction = new QAction(this);
            lAction->setData(lKey);
            lAction->setText(lText);
            lAction->setIcon(lIcon);
            lAction->setShortcut(QKeySequence(lShortcut));
            lAction->setStatusTip(lStatus);
            lMenu->addAction(lAction);

            if(lToolBarOn) {
                lToolBar->addAction(lAction);
            }
        }
    }

    connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(onEvent(QMdiSubWindow*)));

    resize(500, 400);

    setCentralWidget(m_mdiArea);
}
//===============================================
void GPadMdi::onEvent(QAction* _action) {
    QAction* lAction = _action;
    QString lKey = lAction->data().toString();
    //
    if(lKey == "manager/connection") {
        onConnection();
    }
    else if(lKey == "editor/cv") {
        onCv();
    }
    else {
        onErrorKey(lKey);
    }
    GERROR_SHOWG(eGERR);
}
//===============================================
void GPadMdi::onEvent(QMdiSubWindow* _window) {

}
//===============================================
void GPadMdi::onConnection() {
    GLoginUi* lLoginUi = new GLoginUi(this);
    lLoginUi->exec();
    delete lLoginUi;
}
//===============================================
void GPadMdi::onCv() {
    QMdiSubWindow* lSub = new QMdiSubWindow(this);
    GCvUi* lCvUi = new GCvUi(lSub);
    lSub->setWidget(lCvUi);
    m_mdiArea->addSubWindow(lSub);
    lSub->show();
}
//===============================================
