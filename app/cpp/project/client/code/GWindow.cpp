//===============================================
#include "GWindow.h"
//===============================================
GWindow::GWindow(QWidget* parent) : QWidget(parent) {
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
    
    // create
    QPushButton* lCreateButton = new QPushButton;
    lCreateButton->setText("Créer");
    
    QHBoxLayout* lCreateLayout = new QHBoxLayout;
    lCreateLayout->addWidget(lCreateButton);
    lCreateLayout->setAlignment(Qt::AlignRight);
    lCreateLayout->setMargin(0);
   
    // main_layout
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lUsernameLayout);
    lMainLayout->addLayout(lPasswordLayout);
    lMainLayout->addLayout(lConfirmLayout);
    lMainLayout->addLayout(lCreateLayout);
    lMainLayout->setAlignment(Qt::AlignTop);
    
    setLayout(lMainLayout);
    
    connect(lCreateButton, SIGNAL(clicked()), this, SLOT(slotConnect()));
}
//===============================================
GWindow::~GWindow() {

}
//===============================================
void GWindow::slotConnect() {
    QString lUsername = m_usernameEdit->text();
    QString lPassword = m_passwordEdit->text();
    QString lConfirm = m_confirmEdit->text();
    qDebug() << QString("traiter la connexion : (%1 ; %2 ; %3)")
    .arg(lUsername, lPassword, lConfirm);
}
//===============================================
