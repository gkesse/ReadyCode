//===============================================
#include "GQtUserShow.h"
#include "GQtUserModel.h"
#include "GManager.h"
//===============================================
GQtUserShow::GQtUserShow(QWidget* parent) : 
GQtUi(parent) {
	QStringList lHeaderLabels = GManager::Instance()->getTableFields("user_data");
	QVector<QVector<QString>> lDataMap = GManager::Instance()->getTableData("user_data");

	// table
	QTableWidget* lTableWidget = new QTableWidget(0, lHeaderLabels.size());
	lTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	lTableWidget->setHorizontalHeaderLabels(lHeaderLabels);
	lTableWidget->verticalHeader()->show();
	lTableWidget->setShowGrid(true);
	lTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	for(int lCol = 0; lCol < lHeaderLabels.size(); lCol++) {
		lTableWidget->horizontalHeader()->setSectionResizeMode(lCol, QHeaderView::ResizeToContents);
	}
	for(int lRow = 0; lRow < lDataMap.size(); lRow++) {
		QVector<QString> lDataRow = lDataMap.at(lRow);
		lTableWidget->insertRow(lRow);
		for(int lCol = 0; lCol < lHeaderLabels.size(); lCol++) {
			QString lText = lDataRow.at(lCol);
			QTableWidgetItem* lItem = new QTableWidgetItem(lText);
			lTableWidget->setItem(lRow, lCol, lItem);
		}
		lTableWidget->verticalHeader()->setSectionResizeMode(lRow, QHeaderView::ResizeToContents);
	}
	lTableWidget->setMinimumSize(400, 200);

	QHBoxLayout* lTableViewLayout = new QHBoxLayout;
	lTableViewLayout->addWidget(lTableWidget);
	lTableViewLayout->setMargin(0);

	// main_layout
	QVBoxLayout* lMainLayout = new QVBoxLayout;
	lMainLayout->addLayout(lTableViewLayout);
	lMainLayout->setAlignment(Qt::AlignTop);

	setLayout(lMainLayout);

	connect(lTableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onEvent(QPoint)));
	connect(lTableWidget, SIGNAL(cellActivated(int, int)), this, SLOT(onEvent(int, int)));
}
//===============================================
GQtUserShow::~GQtUserShow() {

}
//===============================================
void GQtUserShow::onEvent(const QString& event) {
	qDebug() << event;
}
//===============================================
void GQtUserShow::onEvent(const QPoint& pos) {
	onEvent("menu_contextual");
}
//===============================================
void GQtUserShow::onEvent(int row, int col) {
	onEvent("cell_activate");
}
//===============================================
