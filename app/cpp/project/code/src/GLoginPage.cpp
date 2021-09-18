//===============================================
#include "GLoginPage.h"
#include "GManager.h"
#include "GSQLite.h"
#include "GDialogUi.h"
//===============================================
GLoginPage::GLoginPage(QWidget* parent) :
GProUi(parent) {
	QTextEdit* lTextEdit = new QTextEdit;
	m_textEdit = lTextEdit;
	lTextEdit->setReadOnly(true);
	lTextEdit->setStyleSheet(QString(""
			"QTextEdit {"
			"border:none;"
			"background-color:black;"
			"color:white;"
			"}"
			""));

	QPushButton* lConnectButton = new QPushButton;
	lConnectButton->setText("Se Connecter");
	m_widgetMap[lConnectButton] = "connect";

	QPushButton* lDisconnectButton = new QPushButton;
	lDisconnectButton->setText("Se Déconnecter");
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
	sGApp* lApp = GManager::Instance()->getData()->app;

	if(text == "connect") {
		GDialogUi* lUserConnect = GDialogUi::Create("login/user/connect", this);
		lUserConnect->exec();
		delete lUserConnect;
	}
	else if(text == "disconnect") {

	}
	else if(text == "create") {

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
