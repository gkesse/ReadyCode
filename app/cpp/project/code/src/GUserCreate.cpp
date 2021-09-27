//===============================================
#include "GUserCreate.h"
#include "GManager.h"
//===============================================
GUserCreate::GUserCreate(QWidget* parent) :
GDialogUi(parent) {
    QLabel* lUsernameLabel = new QLabel;
    lUsernameLabel->setText("Nom d'utilisateur :");
    lUsernameLabel->setMinimumWidth(100);

    QLineEdit* lUsernameEdit = new QLineEdit;
    m_usernameEdit = lUsernameEdit;

    QHBoxLayout* lUsernameLayout = new QHBoxLayout;
    lUsernameLayout->addWidget(lUsernameLabel);
    lUsernameLayout->addWidget(lUsernameEdit);
    lUsernameLayout->setMargin(0);

    QLabel* lPasswordLabel = new QLabel;
    lPasswordLabel->setText("Mot de passe :");
    lPasswordLabel->setMinimumWidth(100);

    QLineEdit* lPasswordEdit = new QLineEdit;
    m_passwordEdit = lPasswordEdit;
    lPasswordEdit->setEchoMode(QLineEdit::Password);

    QHBoxLayout* lPasswordLayout = new QHBoxLayout;
    lPasswordLayout->addWidget(lPasswordLabel);
    lPasswordLayout->addWidget(lPasswordEdit);
    lPasswordLayout->setMargin(0);

    QLabel* lConfirmLabel = new QLabel;
    lConfirmLabel->setText("Confirmation :");
    lConfirmLabel->setMinimumWidth(100);

    QLineEdit* lConfirmEdit = new QLineEdit;
    m_confirmEdit = lConfirmEdit;
    lConfirmEdit->setEchoMode(QLineEdit::Password);

    QHBoxLayout* lConfirmLayout = new QHBoxLayout;
    lConfirmLayout->addWidget(lConfirmLabel);
    lConfirmLayout->addWidget(lConfirmEdit);
    lConfirmLayout->setMargin(0);

    QPushButton* lCreateButton = new QPushButton;
    lCreateButton->setText("Créer");
    m_widgetMap[lCreateButton] = "create";

    QHBoxLayout* lConnectLayout = new QHBoxLayout;
    lConnectLayout->addWidget(lCreateButton);
    lConnectLayout->setAlignment(Qt::AlignRight);
    lConnectLayout->setMargin(0);

    // layout
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lUsernameLayout);
    lMainLayout->addLayout(lPasswordLayout);
    lMainLayout->addLayout(lConfirmLayout);
    lMainLayout->addLayout(lConnectLayout);
    lMainLayout->setAlignment(Qt::AlignTop);

    setLayout(lMainLayout);

    setWindowTitle("Login | Créer un utilisateur");
    resize(350, 10);
    setMaximumHeight(0);

    connect(lCreateButton, SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GUserCreate::~GUserCreate() {

}
//===============================================
void GUserCreate::onEvent() {
    QWidget* lWidget = qobject_cast<QWidget*>(sender());
    QString lWidgetId = m_widgetMap[lWidget];
    onEvent(lWidgetId);
}
//===============================================
void GUserCreate::onEvent(const QString& text) {
    if(text == "create") {
        QString lUsername = m_usernameEdit->text();
        QString lPassword = m_passwordEdit->text();
        QString lConfirm = m_confirmEdit->text();
        bool lValid = true;
        lValid &= (lUsername != "");
        lValid &= (lPassword != "");
        lValid &= (lConfirm != "");
        lValid &= (lPassword == lConfirm);
        if(lValid) {
            lValid &= (GManager::Instance()->countUser(lUsername) == 0);
        }
        if(lValid) {
            GManager::Instance()->insertUser(lUsername, lPassword);
            GManager::Instance()->showMessage(this, "Connexion",
                    "La connexion a réussi.");
            accept();
        }
        else {
            GManager::Instance()->showWarning(this, "Connexion",
                    "L'opération a échoué !\n"
                    "Veuillez vérifier les paramètres.");
        }
    }
}
//===============================================
