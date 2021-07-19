//===============================================
#include "GProHome.h"
//===============================================
GProHome::GProHome(QWidget* parent) :
GProUi(parent) {
	GProUi* lList = GProUi::Create("list");
	lList->addItem("home/login", "Connexion");
	lList->addItem("home/sqlite", "SQLite");

	// layout
	QVBoxLayout* lMainLayout = new  QVBoxLayout;
	lMainLayout->addWidget(lList);
	lMainLayout->setAlignment(Qt::AlignTop);
	lMainLayout->setMargin(0);
	lMainLayout->setSpacing(0);

	setLayout(lMainLayout);
}
//===============================================
GProHome::~GProHome() {

}
//===============================================
