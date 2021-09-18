//===============================================
#include "GSchemaShow.h"
#include "GManager.h"
//===============================================
GSchemaShow::GSchemaShow(QWidget* parent) :
GDialogUi(parent) {
	QLabel* lLabel = new QLabel;
	lLabel->setText("Table :");

	QVector<QString> lTables = GManager::Instance()->getTables();

	QComboBox* lTable = new QComboBox;
	m_table = lTable;
	lTable->addItems(lTables.toList());

	QPushButton* lRun = new QPushButton;
	lRun->setText("Schema");
	m_widgetMap[lRun] = "run";

	QHBoxLayout* lRowLayout = new QHBoxLayout;
	lRowLayout->addWidget(lLabel);
	lRowLayout->addWidget(lTable, 1);
	lRowLayout->addWidget(lRun);
	lRowLayout->setMargin(0);

	// layout
	QHBoxLayout* lMainLayout = new QHBoxLayout;
	lMainLayout->addLayout(lRowLayout);

	setLayout(lMainLayout);

	setWindowTitle("SQLite | Afficher le schema");
	resize(350, 10);
	setMaximumHeight(0);

	connect(lRun, SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GSchemaShow::~GSchemaShow() {

}
//===============================================
void GSchemaShow::onEvent() {
	QWidget* lWidget = qobject_cast<QWidget*>(sender());
	QString lWidgetId = m_widgetMap[lWidget];
	onEvent(lWidgetId);
}
//===============================================
void GSchemaShow::onEvent(const QString& text) {
	if(text == "run") {
		m_dataMap["table"] = m_table->currentText();
		accept();
	}
}
//===============================================
