//===============================================
#include "GQtUserShow.h"
#include "GQtUserModel.h"
#include "GManager.h"
//===============================================
GQtUserShow::GQtUserShow(QWidget* parent) : 
GQtUi(parent) {
	// header_label
    QStringList lHeaderLabels = GManager::Instance()->getTableFields("users");

    // table
	QTableWidget* lTableWidget = new QTableWidget(5, lHeaderLabels.size());
    lTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    lTableWidget->setHorizontalHeaderLabels(lHeaderLabels);
    lTableWidget->verticalHeader()->show();
    lTableWidget->setShowGrid(true);
    lTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    for(int i = 0; i < lHeaderLabels.size(); i++) {
        lTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    
    QHBoxLayout* lTableViewLayout = new QHBoxLayout;
    lTableViewLayout->addWidget(lTableWidget);
    lTableViewLayout->setMargin(0);
   
    // main_layout
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lTableViewLayout);
    lMainLayout->setAlignment(Qt::AlignTop);
    
    setLayout(lMainLayout);

    connect(lTableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotEvent(QPoint)));
    connect(lTableWidget, SIGNAL(cellActivated(int, int)), this, SLOT(slotEvent(int, int)));
}
//===============================================
GQtUserShow::~GQtUserShow() {

}
//===============================================
void GQtUserShow::onEvent(const QString& event) {
	qDebug() << event;
}
//===============================================
void GQtUserShow::slotEvent(const QPoint& pos) {
	onEvent("menu_contextual");
}
//===============================================
void GQtUserShow::slotEvent(int row, int col) {
	onEvent("cell_activate");
}
//===============================================
