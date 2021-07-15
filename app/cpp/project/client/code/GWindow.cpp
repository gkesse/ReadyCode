//===============================================
#include "GWindow.h"
//===============================================
GWindow::GWindow(QWidget* parent) : QWidget(parent) {    
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
    
    QPushButton* lConnectButton = new QPushButton;
    lConnectButton->setText("Connexion");
    
    QHBoxLayout* lConnectLayout = new QHBoxLayout;
    lConnectLayout->addWidget(lConnectButton);
    lConnectLayout->setAlignment(Qt::AlignRight);
    lConnectLayout->setMargin(0);
   
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lUsernameLayout);
    lMainLayout->addLayout(lPasswordLayout);
    lMainLayout->addLayout(lConnectLayout);
    lMainLayout->setAlignment(Qt::AlignTop);
    
    setLayout(lMainLayout);
    
    connect(lConnectButton, SIGNAL(clicked()), this, SLOT(slotConnect()));
}
//===============================================
GWindow::~GWindow() {

}
//===============================================
void GWindow::slotConnect() {
    QString lUsername = m_usernameEdit->text();
    QString lPassword = m_passwordEdit->text();
    qDebug() << QString("traiter la connexion : (%1 ; %2)")
    .arg(lUsername, lPassword);
}
//===============================================
