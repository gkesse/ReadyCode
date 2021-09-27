//===============================================
#include "GLoginPage.h"
#include "GManager.h"
#include "GDialogUi.h"
//===============================================
GLoginPage::GLoginPage(QWidget* parent) :
GProUi(parent) {
    sGApp* lApp = GManager::Instance()->getData()->app;

    QTextEdit* lTextEdit = new QTextEdit;
    m_textEdit = lTextEdit;
    lTextEdit->setReadOnly(true);
    lTextEdit->setLineWrapMode(QTextEdit::NoWrap);
    lTextEdit->setStyleSheet(QString(""
            "QTextEdit {"
            "border:none;"
            "background-color:black;"
            "color:white;"
            "font-family:courier;"
            "}"
            ""));

    bool lLoginOn = (GManager::Instance()->countLogin() != 0);

    QPushButton* lConnectButton = new QPushButton;
    lApp->login_connect = lConnectButton;
    lConnectButton->setText("Se Connecter");
    lConnectButton->setEnabled(!lLoginOn);
    m_widgetMap[lConnectButton] = "connect";

    QPushButton* lDisconnectButton = new QPushButton;
    lApp->login_disconnect = lDisconnectButton;
    lDisconnectButton->setText("Se Déconnecter");
    lDisconnectButton->setEnabled(lLoginOn);
    m_widgetMap[lDisconnectButton] = "disconnect";

    QPushButton* lCreateButton = new QPushButton;
    lCreateButton->setText("Créer");
    m_widgetMap[lCreateButton] = "create";

    QPushButton* lUpdateButton = new QPushButton;
    lUpdateButton->setText("Modifier");
    m_widgetMap[lUpdateButton] = "update";

    QPushButton* lDeleteButton = new QPushButton;
    lDeleteButton->setText("Supprimer");
    m_widgetMap[lDeleteButton] = "delete";

    QVBoxLayout* lButtonLayout = new QVBoxLayout;
    lButtonLayout->addWidget(lConnectButton);
    lButtonLayout->addWidget(lDisconnectButton);
    lButtonLayout->addWidget(lCreateButton);
    lButtonLayout->addWidget(lUpdateButton);
    lButtonLayout->setAlignment(Qt::AlignTop);
    lButtonLayout->setMargin(0);

    // layout
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->addWidget(lTextEdit);
    lMainLayout->addLayout(lButtonLayout);

    setLayout(lMainLayout);

    connect(lConnectButton, SIGNAL(clicked()), this, SLOT(onEvent()));
    connect(lDisconnectButton, SIGNAL(clicked()), this, SLOT(onEvent()));
    connect(lCreateButton, SIGNAL(clicked()), this, SLOT(onEvent()));
    connect(lUpdateButton, SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GLoginPage::~GLoginPage() {

}
//===============================================
void GLoginPage::onEvent() {
    QWidget* lWidget = qobject_cast<QWidget*>(sender());
    QString lWidgetId = m_widgetMap[lWidget];
    onEvent(lWidgetId);
}
//===============================================
void GLoginPage::onEvent(const QString& text) {
    if(text == "connect") {
        GDialogUi* lUserConnect = GDialogUi::Create("login/user/connect", this);
        lUserConnect->exec();
        GManager::Instance()->updateLogin();
        delete lUserConnect;
    }
    else if(text == "disconnect") {
        int lOk = GManager::Instance()->confirm(this);
        if(lOk != QMessageBox::Ok) {return;}
        GManager::Instance()->logOut();
        GManager::Instance()->updateLogin();
        m_textEdit->setText("L'opération a été réalisée avec succès...");
    }
    else if(text == "create") {
        GDialogUi* lCreateUi = GDialogUi::Create("login/user/create", this);
        int lOk = lCreateUi->exec();
        if(lOk == QDialog::Rejected) {delete lCreateUi; return;}
        QString lTable = lCreateUi->getData().value("table");
        if(lTable == "") {delete lCreateUi; return;}
        delete lCreateUi;
        m_textEdit->setText("L'opération a été réalisée avec succès...");
    }
    else if(text == "update") {

    }
    else if(text == "delete") {

    }
}
//===============================================
void GLoginPage::setTitle() {
    setWindowTitle("ReadyApp | Login");
}
//===============================================
