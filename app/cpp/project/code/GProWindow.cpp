//===============================================
#include "GProWindow.h"
//===============================================
GProWindow::GProWindow(QWidget* parent) :
GProUi(parent) {
	// workspace
	GProUi* lWorkspace = GProUi::Create("stack");
	lWorkspace->addPage("home", "Accueil", GProUi::Create("home"), 1);
	lWorkspace->addPage("login", "Connexion", GProUi::Create("login"));

	// layout
	QVBoxLayout* lMainLayout = new QVBoxLayout;
	lMainLayout->addWidget(lWorkspace);
	lMainLayout->setAlignment(Qt::AlignTop);
	lMainLayout->setMargin(0);
	lMainLayout->setSpacing(0);

	setLayout(lMainLayout);
}
//===============================================
GProWindow::~GProWindow() {

}
//===============================================
