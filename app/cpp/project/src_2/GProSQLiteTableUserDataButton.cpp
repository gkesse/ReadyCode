//===============================================
#include "GProSQLiteTableUserDataButton.h"
#include "GManager.h"
#include "GSQLite.h"
//===============================================
GProSQLiteTableUserDataButton::GProSQLiteTableUserDataButton(QWidget* parent) :
GProUi(parent) {
	// button
	GProUi* lButtons = GProUi::Create("list");
	lButtons->addItem("add", "Ajouter");

	// layout
	QHBoxLayout* lMainLayout = new  QHBoxLayout;
	lMainLayout->addWidget(lButtons);
	lMainLayout->setAlignment(Qt::AlignTop);
	lMainLayout->setMargin(0);
	lMainLayout->setSpacing(0);

	setLayout(lMainLayout);

	connect(lButtons, SIGNAL(emitEvent(QString)), this, SLOT(onEvent(QString)));
}
//===============================================
GProSQLiteTableUserDataButton::~GProSQLiteTableUserDataButton() {

}
//===============================================
void GProSQLiteTableUserDataButton::onEvent(const QString& text) {
	if(text == "add") {
		GManager::Instance()->setPage("home/sqlite/table/user_data/add", "home/sqlite/table/add_user");
	}
}
//===============================================
