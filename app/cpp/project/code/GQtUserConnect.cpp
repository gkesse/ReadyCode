//===============================================
#include "GQtUserConnect.h"
#include "GManager.h"
//===============================================
GQtUserConnect::GQtUserConnect(QWidget* parent) :
GQtUi(parent) {
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

	// connect
	QPushButton* lConnectButton = new QPushButton;
	lConnectButton->setText("Connexion");
	m_widgetMap[lConnectButton] = "connect";

	QHBoxLayout* lConnectLayout = new QHBoxLayout;
	lConnectLayout->addWidget(lConnectButton);
	lConnectLayout->setAlignment(Qt::AlignRight);
	lConnectLayout->setMargin(0);

	// layout
	QVBoxLayout* lMainLayout = new QVBoxLayout;
	lMainLayout->addLayout(lUsernameLayout);
	lMainLayout->addLayout(lPasswordLayout);
	lMainLayout->addLayout(lConnectLayout);
	lMainLayout->setAlignment(Qt::AlignTop);

	setLayout(lMainLayout);

	connect(lConnectButton, SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GQtUserConnect::~GQtUserConnect() {

}
//===============================================
void GQtUserConnect::onEvent() {
	QWidget* lWidget = qobject_cast<QWidget*>(sender());
	QString lWidgetId = m_widgetMap[lWidget];
	onEvent(lWidgetId);
}
//===============================================
void GQtUserConnect::onEvent(const QString& text) {
	if(text == "connect") {
		QString lUsername = m_usernameEdit->text();
		QString lPassword = m_passwordEdit->text();
		bool lValid = true;
		lValid &= (lUsername != "");
		lValid &= (lPassword != "");
		if(lValid) {
			lValid &= GManager::Instance()->countUser(lUsername, lPassword);
		}
		if(lValid) {
	        GManager::Instance()->showMessage(this, "Connexion",
	        "La connexion a réussi.");
	    }
	    else {
	        GManager::Instance()->showWarning(this, "Connexion",
	        "La connexion a échoué !\n"
	        "Veuillez vérifier les paramètres.");
	    }
	}
}
//===============================================
