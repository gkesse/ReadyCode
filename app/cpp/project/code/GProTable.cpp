//===============================================
#include "GProTable.h"
#include "GManager.h"
//===============================================
GProTable::GProTable(QWidget* parent) :
GProUi(parent) {
	QTableWidget* lTableWidget = new QTableWidget;
	m_tableWidget = lTableWidget;
	lTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	lTableWidget->verticalHeader()->show();
	lTableWidget->setShowGrid(true);
	lTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	lTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

	lTableWidget->setMinimumSize(400, 200);

	// layout
	QVBoxLayout* lMainLayout = new  QVBoxLayout;
	lMainLayout->addWidget(lTableWidget);
	lMainLayout->setAlignment(Qt::AlignTop);
	lMainLayout->setMargin(0);
	lMainLayout->setSpacing(0);

	setLayout(lMainLayout);

	connect(lTableWidget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(onEvent(int, int)));
}
//===============================================
GProTable::~GProTable() {

}
//===============================================
void GProTable::loadData(QStringList headers, QVector<QVector<QString>> datas) {
	m_tableWidget->clear();
	m_tableWidget->setRowCount(0);
	m_tableWidget->setColumnCount(headers.size());

	m_tableWidget->setHorizontalHeaderLabels(headers);

	for(int lCol = 0; lCol < headers.size(); lCol++) {
		m_tableWidget->horizontalHeader()->setSectionResizeMode(lCol, QHeaderView::ResizeToContents);
	}

	for(int lRow = 0; lRow < datas.size(); lRow++) {
		QVector<QString> lDataRow = datas.at(lRow);
		m_tableWidget->insertRow(lRow);
		for(int lCol = 0; lCol < headers.size(); lCol++) {
			QString lText = lDataRow.at(lCol);
			QTableWidgetItem* lItem = new QTableWidgetItem(lText);
			m_tableWidget->setItem(lRow, lCol, lItem);
		}
		m_tableWidget->verticalHeader()->setSectionResizeMode(lRow, QHeaderView::ResizeToContents);
	}
}
//===============================================
void GProTable::onEvent(int row, int col) {
	emit emitEvent(m_tableWidget, row, col);
}
//===============================================
