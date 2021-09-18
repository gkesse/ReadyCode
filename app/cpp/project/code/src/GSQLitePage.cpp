//===============================================
#include "GSQLitePage.h"
#include "GManager.h"
#include "GDialogUi.h"
//===============================================
GSQLitePage::GSQLitePage(QWidget* parent) :
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
GSQLitePage::~GSQLitePage() {

}
//===============================================
void GSQLitePage::onEvent() {
	QWidget* lWidget = qobject_cast<QWidget*>(sender());
	QString lWidgetId = m_widgetMap[lWidget];
	onEvent(lWidgetId);
}
//===============================================
void GSQLitePage::onEvent(const QString& text) {
	sGApp* lApp = GManager::Instance()->getData()->app;

	if(text == "master") {
		GManager::Instance()->runCmd(QString("bash %1")
				.arg(lApp->sqlite_sql_master));
	}
	else if(text == "tables") {
		QVector<QString> lTables = GManager::Instance()->getTables();
		GManager::Instance()->setData2(m_textEdit, lTables);
	}
	else if(text == "schema") {
		GDialogUi* lSchemaUi = GDialogUi::Create("sqlite/schema/show", this);
		int lOk = lSchemaUi->exec();
		if(lOk == QDialog::Rejected) {delete lSchemaUi; return;}
		QString lTable = lSchemaUi->getData().value("table");
		if(lTable == "") {delete lSchemaUi; return;}
		QString lSchema = GManager::Instance()->getSchema(lTable);
		m_textEdit->setText(lSchema.toUpper());
		delete lSchemaUi;
	}
	else if(text == "update") {
		QStringList lFilters = QStringList() << "*.sh";
		QStringList lFiles = GManager::Instance()->getDirFiles(lApp->sqlite_sql_path, lFilters);
		for(int i = 0; i < lFiles.size(); i++) {
			QString lFile = lFiles.at(i);
			QString lFilename = QFileInfo(lFile).baseName();
			QString lFileId = lFilename.split('_').first();
			int lCount = GManager::Instance()->countFileId(lFileId);
			m_textEdit->setText(QString("%1").arg(lCount));

		}
	}
}
//===============================================
void GSQLitePage::setTitle() {
	setWindowTitle("SQLite | Modifier la base de données");
}
//===============================================
