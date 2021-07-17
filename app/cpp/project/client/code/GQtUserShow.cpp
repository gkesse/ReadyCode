//===============================================
#include "GQtUserShow.h"
#include "GQtUserModel.h"
#include "GManager.h"
//===============================================
GQtUserShow::GQtUserShow(QWidget* parent) : 
GQtUi(parent) {
	// table
	QTableWidget* lTableWidget = new QTableWidget(0, 2);
    lTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList lHeaderLabels;
    lHeaderLabels << tr("Filename") << tr("Size");
    lTableWidget->setHorizontalHeaderLabels(lHeaderLabels);
    lTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    lTableWidget->verticalHeader()->hide();
    lTableWidget->setShowGrid(false);
    
    QHBoxLayout* lTableViewLayout = new QHBoxLayout;
    lTableViewLayout->addWidget(lTableWidget);
    lTableViewLayout->setMargin(0);
   
    // main_layout
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lTableViewLayout);
    lMainLayout->setAlignment(Qt::AlignTop);
    
    setLayout(lMainLayout);
}
//===============================================
GQtUserShow::~GQtUserShow() {

}
//===============================================
