//===============================================
#include "GProSQLiteTableUserDataAdd.h"
#include "GManager.h"
#include "GSQLite.h"
//===============================================
GProSQLiteTableUserDataAdd::GProSQLiteTableUserDataAdd(QWidget* parent) :
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
GProSQLiteTableUserDataAdd::~GProSQLiteTableUserDataAdd() {

}
//===============================================
void GProSQLiteTableUserDataAdd::onEvent(const QString& text) {
	qDebug() << text;
}
//===============================================
