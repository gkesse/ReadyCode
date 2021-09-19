//===============================================
#include "GTableDelete.h"
#include "GManager.h"
//===============================================
GTableDelete::GTableDelete(QWidget* parent) :
GDialogUi(parent) {
	QLabel* lLabel = new QLabel;
	lLabel->setText("Table :");

	QVector<QString> lTables = GManager::Instance()->getTables();

	QComboBox* lTable = new QComboBox;
	m_table = lTable;
	GManager::Instance()->setData2(lTable, lTables);

	QPushButton* lDelete = new QPushButton;
	lDelete->setText("Supprimer");
	m_widgetMap[lDelete] = "delete";

	QHBoxLayout* lRowLayout = new QHBoxLayout;
	lRowLayout->addWidget(lLabel);
	lRowLayout->addWidget(lTable, 1);
	lRowLayout->addWidget(lDelete);
	lRowLayout->setMargin(0);

	// layout
	QHBoxLayout* lMainLayout = new QHBoxLayout;
	lMainLayout->addLayout(lRowLayout);

	setLayout(lMainLayout);

	setWindowTitle("SQLite | Supprimer une table");
	resize(350, 10);
	setMaximumHeight(0);

	connect(lDelete, SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GTableDelete::~GTableDelete() {

}
//===============================================
void GTableDelete::onEvent() {
	QWidget* lWidget = qobject_cast<QWidget*>(sender());
	QString lWidgetId = m_widgetMap[lWidget];
	onEvent(lWidgetId);
}
//===============================================
void GTableDelete::onEvent(const QString& text) {
	if(text == "delete") {
		m_dataMap["table"] = m_table->currentText().toLower();
		int lOk = GManager::Instance()->confirm(this);
		if(lOk != QMessageBox::Ok) {return;}
		accept();
	}
}
//===============================================
