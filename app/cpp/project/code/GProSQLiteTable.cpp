//===============================================
#include "GProSQLiteTable.h"
#include "GManager.h"
#include "GSQLite.h"
//===============================================
GProSQLiteTable::GProSQLiteTable(QWidget* parent) :
GProUi(parent) {
	// table
	QPushButton* lTableTitle = new QPushButton;
	m_tableTitle = lTableTitle;

	GProUi* lTable = GProUi::Create("table");
	m_table = lTable;

	QVBoxLayout* lTableLayout = new  QVBoxLayout;
	lTableLayout->addWidget(lTableTitle);
	lTableLayout->addWidget(lTable);
	lTableLayout->setAlignment(Qt::AlignTop);
	lTableLayout->setMargin(0);
	lTableLayout->setSpacing(0);

	// boutons
	GProUi* lButtonStack = GProUi::Create("stack");
	m_buttonStack = lButtonStack;
	lButtonStack->addPage("default", "", GProUi::Create("default"), 1);
	lButtonStack->addPage("user_data", "", GProUi::Create("sqlitetable/user_data/button"));

	// layout
	QHBoxLayout* lMainLayout = new  QHBoxLayout;
	lMainLayout->addLayout(lTableLayout, 1);
	lMainLayout->addWidget(lButtonStack);
	lMainLayout->setAlignment(Qt::AlignTop);
	lMainLayout->setMargin(0);

	setLayout(lMainLayout);
}
//===============================================
GProSQLiteTable::~GProSQLiteTable() {

}
//===============================================
int GProSQLiteTable::loadPage() {
	sGApp* lApp = GManager::Instance()->getData()->app;
	QString lTitle = QString("SQLite | Données de la table (%1)")
					.arg(lApp->sqlite_table_name);
	lApp->title_bar->setTitle(lTitle);
	m_tableTitle->setText(lApp->sqlite_table_name);
	QString lKey = m_buttonStack->getKey(lApp->sqlite_table_name, "default");
	m_buttonStack->setPage(lKey);
	QStringList lHeaders = GManager::Instance()->getTableFields(lApp->sqlite_table_name);
	QVector<QVector<QString>> lDatas = GSQLite::Instance()->readMap(QString(""
			"select * from %1\n"
			"").arg(lApp->sqlite_table_name));
	m_table->loadData(lHeaders, lDatas);
	return 1;
}
//===============================================
