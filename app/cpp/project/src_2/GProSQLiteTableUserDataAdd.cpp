//===============================================
#include "GProSQLiteTableUserDataAdd.h"
#include "GManager.h"
//===============================================
GProSQLiteTableUserDataAdd::GProSQLiteTableUserDataAdd(QWidget* parent) :
GProUi(parent) {
    // username
    QLabel* lUsernameLabel = new QLabel;
    lUsernameLabel->setText("Nom d'utilisateur :");
    lUsernameLabel->setMinimumWidth(100);

    QLineEdit* lUsernameEdit = new QLineEdit;
    m_usernameEdit = lUsernameEdit;

    QHBoxLayout* lUsernameLayout = new QHBoxLayout;
    lUsernameLayout->addWidget(lUsernameLabel);
    lUsernameLayout->addWidget(lUsernameEdit);
    lUsernameLayout->setMargin(0);

    // password
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

    // confirm
    QLabel* lConfirmLabel = new QLabel;
    lConfirmLabel->setText("Confirmer :");
    lConfirmLabel->setMinimumWidth(100);

    QLineEdit* lConfirmEdit = new QLineEdit;
    m_confirmEdit = lConfirmEdit;
    lConfirmEdit->setEchoMode(QLineEdit::Password);

    QHBoxLayout* lConfirmLayout = new QHBoxLayout;
    lConfirmLayout->addWidget(lConfirmLabel);
    lConfirmLayout->addWidget(lConfirmEdit);
    lConfirmLayout->setMargin(0);

    // save
    QPushButton* lCancelButton = new QPushButton;
    lCancelButton->setText("Annuler");

    QPushButton* lSaveButton = new QPushButton;
    lSaveButton->setText("Enregistrer");

    QHBoxLayout* lButtonLayout = new QHBoxLayout;
    lButtonLayout->addWidget(lSaveButton);
    lButtonLayout->addWidget(lCancelButton);
    lButtonLayout->setAlignment(Qt::AlignRight);
    lButtonLayout->setMargin(0);

    // main_layout
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lUsernameLayout);
    lMainLayout->addLayout(lPasswordLayout);
    lMainLayout->addLayout(lConfirmLayout);
    lMainLayout->addLayout(lButtonLayout);
    lMainLayout->setAlignment(Qt::AlignTop);
    lMainLayout->setMargin(0);

    setLayout(lMainLayout);

    connect(lSaveButton, SIGNAL(clicked()), this, SLOT(onEvent()));
    connect(lCancelButton, SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GProSQLiteTableUserDataAdd::~GProSQLiteTableUserDataAdd() {

}
//===============================================
void GProSQLiteTableUserDataAdd::onEvent() {
    QString lUsername = m_usernameEdit->text();
    QString lPassword = m_passwordEdit->text();
    QString lConfirm = m_confirmEdit->text();
    bool lValid = true;
    lValid &= (lUsername != "");
    lValid &= (lPassword != "");
    lValid &= (lConfirm != "");
    lValid &= (lPassword == lConfirm);
    if(lValid) {
    	lValid &= (GManager::Instance()->countUser(lUsername) != 0);
    }
    if(lValid) {
        GManager::Instance()->saveUser(lUsername, lPassword);
        m_usernameEdit->clear();
        m_passwordEdit->clear();
        m_confirmEdit->clear();
        GManager::Instance()->showMessage(this, "Enregistrement",
        "L'enregistrement a réussi.");
    }
    else {
        GManager::Instance()->showWarning(this, "Enregistrement",
        "L'enregistrement a échoué !\n"
        "Veuillez vérifier les paramètres.");
    }
}
//===============================================
