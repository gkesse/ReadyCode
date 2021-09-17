//===============================================
#include "GProSQLite.h"
#include "GManager.h"
#include "GSQLite.h"
//===============================================
GProSQLite::GProSQLite(QWidget* parent) :
GProUi(parent) {
	QStringList lHeaders; lHeaders << "TABLE_NAME";
	QVector<QVector<QString>> lDatas = GSQLite::Instance()->readMap(QString(""
			"select name from sqlite_master\n"
			"where type = 'table'\n"
			"order by name"
			""));

	// table
	GProUi* lTable = GProUi::Create("table");
	lTable->loadData(lHeaders, lDatas);

	// boutons
	QPushButton* lUpdateButton = new QPushButton;
	lUpdateButton->setText("Mettre à jour");
	m_widgetMap[lUpdateButton] = "update";

	QVBoxLayout* lButtonLayout = new  QVBoxLayout;
	lButtonLayout->addWidget(lUpdateButton);
	lButtonLayout->setAlignment(Qt::AlignTop);
	lButtonLayout->setMargin(0);
	lButtonLayout->setSpacing(0);

	// layout
	QHBoxLayout* lMainLayout = new  QHBoxLayout;
	lMainLayout->addWidget(lTable);
	lMainLayout->addLayout(lButtonLayout);
	lMainLayout->setAlignment(Qt::AlignTop);
	lMainLayout->setMargin(0);

	setLayout(lMainLayout);

	connect(lTable, SIGNAL(emitEvent(QTableWidget*, int, int)), this, SLOT(onEvent(QTableWidget*, int, int)));
	connect(lUpdateButton, SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GProSQLite::~GProSQLite() {

}
//===============================================
void GProSQLite::onEvent(QTableWidget* tableWidget, int row, int col) {
	sGApp* lApp = GManager::Instance()->getData()->app;
	QTableWidgetItem* lItem = tableWidget->item(row, 0);
	QString lTable = lItem->data(Qt::DisplayRole).toString();
	lApp->sqlite_table_name = lTable;
	GManager::Instance()->setPage("home/sqlite/table");
}
//===============================================
void GProSQLite::onEvent() {
	QWidget* lWidget = qobject_cast<QWidget*>(sender());
	QString lWidgetId = m_widgetMap[lWidget];
	onEvent(lWidgetId);
}
//===============================================
void GProSQLite::onEvent(const QString& text) {
	qDebug() << text;
}
//===============================================
