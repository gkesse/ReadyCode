//===============================================
#include "GProWindow.h"
#include "GManager.h"
//===============================================
GProWindow::GProWindow(QWidget* parent) :
GProUi(parent) {
	sGApp* lApp = GManager::Instance()->getData()->app;

	// address_key
	GProUi* lAddressKey = GProUi::Create("addresskey");
	lApp->address_key = lAddressKey;

	// workspace
	GProUi* lWorkspace = GProUi::Create("stack");
	lApp->page_map = lWorkspace;
	lWorkspace->addPage("home", "Accueil", GProUi::Create("home"), 1);
	lWorkspace->addPage("home/login", "Connexion", GProUi::Create("login"));
	lWorkspace->addPage("home/sqlite", "SQLite", GProUi::Create("sqlite"));
	lWorkspace->addPage("home/sqlite/table", "SQLite", GProUi::Create("sqlitetable"));

	GManager::Instance()->setPage(lWorkspace->getDefaultKey());

	// layout
	QVBoxLayout* lMainLayout = new QVBoxLayout;
	lMainLayout->addWidget(lAddressKey);
	lMainLayout->addWidget(lWorkspace, 1);
	lMainLayout->setAlignment(Qt::AlignTop);

	setLayout(lMainLayout);
}
//===============================================
GProWindow::~GProWindow() {

}
//===============================================
