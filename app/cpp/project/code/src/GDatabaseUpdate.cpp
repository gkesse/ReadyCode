//===============================================
#include "GDatabaseUpdate.h"
#include "GManager.h"
#include "GSQLite.h"
#include "GDialogUi.h"
//===============================================
GDatabaseUpdate::GDatabaseUpdate(QWidget* parent) :
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

	QPushButton* lMasterButton = new QPushButton;
	lMasterButton->setText("Master");
	m_widgetMap[lMasterButton] = "master";

	QPushButton* lTablesButton = new QPushButton;
	lTablesButton->setText("Tables");
	m_widgetMap[lTablesButton] = "tables";

	QPushButton* lSchemaButton = new QPushButton;
	lSchemaButton->setText("Schema");
	m_widgetMap[lSchemaButton] = "schema";

	QPushButton* lUpdateButton = new QPushButton;
	lUpdateButton->setText("Modifier");
	m_widgetMap[lUpdateButton] = "update";

	QVBoxLayout* lButtonLayout = new QVBoxLayout;
	lButtonLayout->addWidget(lMasterButton);
	lButtonLayout->addWidget(lTablesButton);
	lButtonLayout->addWidget(lSchemaButton);
	lButtonLayout->addWidget(lUpdateButton);
	lButtonLayout->setAlignment(Qt::AlignTop);
	lButtonLayout->setMargin(0);

	// layout
	QHBoxLayout* lMainLayout = new QHBoxLayout;
	lMainLayout->addWidget(lTextEdit);
	lMainLayout->addLayout(lButtonLayout);

	setLayout(lMainLayout);

	connect(lMasterButton, SIGNAL(clicked()), this, SLOT(onEvent()));
	connect(lTablesButton, SIGNAL(clicked()), this, SLOT(onEvent()));
	connect(lSchemaButton, SIGNAL(clicked()), this, SLOT(onEvent()));
	connect(lUpdateButton, SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GDatabaseUpdate::~GDatabaseUpdate() {

}
//===============================================
void GDatabaseUpdate::onEvent() {
	QWidget* lWidget = qobject_cast<QWidget*>(sender());
	QString lWidgetId = m_widgetMap[lWidget];
	onEvent(lWidgetId);
}
//===============================================
void GDatabaseUpdate::onEvent(const QString& text) {
	sGApp* lApp = GManager::Instance()->getData()->app;

	if(text == "master") {
		GManager::Instance()->runCmd(QString("bash %1")
				.arg(lApp->sqlite_sql_master));
	}
	else if(text == "tables") {
		QVector<QString> lTables = GSQLite::Instance()->readCol(QString(""
				"select name from sqlite_master\n"
				"where type = 'table'\n"
				""));
		qDebug() << lTables;
	}
	else if(text == "schema") {
		GDialogUi* lSchemaUi = GDialogUi::Create("sqlite/schema/show", this);
		int lOk = lSchemaUi->exec();

		if(lOk == QDialog::Rejected) {delete lSchemaUi; return;}

		QString lTable = lSchemaUi->getData().value("table");

		if(lTable == "") {delete lSchemaUi; return;}

		QString lSchema = GSQLite::Instance()->readData(QString(""
				"select sql from sqlite_master\n"
				"where type = 'table'\n"
				"and name = '%1'\n"
				"").arg(lTable));

		m_textEdit->append(lSchema);

		delete lSchemaUi;
	}
	else if(text == "update") {
		QStringList lFilters = QStringList() << "*.sh";
		QStringList lFiles = GManager::Instance()->getDirFiles(lApp->sqlite_sql_path, lFilters);
		for(int i = 0; i < lFiles.size(); i++) {
			QString lFile = lFiles.at(i);
			QString lFilename = QFileInfo(lFile).baseName();
			QString lFileId = lFilename.split('_').first();
			int lCount = GSQLite::Instance()->readData(QString(""
					"select count(*) from file_id_data\n"
					"where file_id = '%1'"
					"").arg(lFileId)).toInt();

			qDebug() << lFileId;
		}
	}
}
//===============================================
void GDatabaseUpdate::setTitle() {
	setWindowTitle("SQLite | Modifier la base de données");
}
//===============================================
