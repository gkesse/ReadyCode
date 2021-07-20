//===============================================
#include "GProSQLiteTableButtonUserData.h"
#include "GManager.h"
#include "GSQLite.h"
//===============================================
GProSQLiteTableButtonUserData::GProSQLiteTableButtonUserData(QWidget* parent) :
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
GProSQLiteTableButtonUserData::~GProSQLiteTableButtonUserData() {

}
//===============================================
void GProSQLiteTableButtonUserData::onEvent(const QString& text) {
	qDebug() << text;
}
//===============================================
