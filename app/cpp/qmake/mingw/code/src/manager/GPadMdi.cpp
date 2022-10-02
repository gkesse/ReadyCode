//===============================================
#include <GLog.h>
#include "GPadMdi.h"
#include "GTitleBarApp.h"
#include "GLoginUi.h"
#include "GLogoutUi.h"
#include "GAccountUi.h"
#include "GCvUi.h"
#include "GStyle.h"
#include "GPath.h"
#include "GPicto.h"
#include "GConnection.h"
#include "GClient.h"
//===============================================
GPadMdi::GPadMdi(QWidget* _parent)
: GMainWindow(_parent) {
    createDoms();
    createLayout();
}
//===============================================
GPadMdi::~GPadMdi() {
    delete m_connection;
}
//===============================================
void GPadMdi::createLayout() {
    m_titleBar = new GTitleBarApp(this);

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

    setObjectName("flat");
    setCentralWidget(m_mdiArea);
    resize(500, 400);

    connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(onEvent(QMdiSubWindow*)));

    m_connection = new GConnection();
}
//===============================================
void GPadMdi::onEvent(QAction* _action) {
    QAction* lAction = _action;
    QString lKey = lAction->data().toString();
    // connection
    if(lKey == "connection/run_connection") {
        onRunConnection();
    }
    else if(lKey == "connection/create_group") {
        onCreateGroup();
    }
    else if(lKey == "manager/account") {
        onAccount();
    }
    // editor
    else if(lKey == "editor/cv") {
        onCv();
    }
    else if(lKey == "poco/client/tcp") {
        onPocoClientTcp();
    }
    else {
        onErrorKey(lKey);
    }
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGERR);
}
//===============================================
void GPadMdi::onEvent(QMdiSubWindow* _window) {

}
//===============================================
void GPadMdi::onRunConnection() {
    if(!m_connection->isConnect()) {
        GLoginUi* lLoginUi = new GLoginUi(m_connection, this);
        lLoginUi->exec();
        if(m_connection->isConnect()) {
            m_titleBar->setPseudo(m_connection->getPseudo());
        }
    }
    else {
        GLogoutUi* lLogoutUi = new GLogoutUi(m_connection, this);
        lLogoutUi->exec();
        delete lLogoutUi;
        if(!m_connection->isConnect()) {
            delete m_connection;
            m_connection = new GConnection();
            m_titleBar->setPseudo("Connexion");
        }
    }
}
//===============================================
void GPadMdi::onCreateGroup() {

}
//===============================================
void GPadMdi::onAccount() {
    GAccountUi* lAccountUi = new GAccountUi(this);
    lAccountUi->exec();
}
//===============================================
void GPadMdi::onCv() {
    QMdiSubWindow* lSub = new QMdiSubWindow(this);
    GCvUi* lCvUi = new GCvUi(lSub);
    lSub->setWidget(lCvUi);
    m_mdiArea->addSubWindow(lSub);
    lSub->setWindowTitle("Editeur de CV");
    lSub->show();
}
//===============================================
void GPadMdi::onPocoClientTcp() {
    GCALL_SERVER("opencv", "create_image");
}
//===============================================
GConnection* GPadMdi::getConnection() const {
    return m_connection;
}
//===============================================
