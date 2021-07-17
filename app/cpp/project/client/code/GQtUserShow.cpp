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

    connect(lTableWidget, &QTableWidget::customContextMenuRequested,
            this, &Window::contextMenu);
    connect(lTableWidget, &QTableWidget::cellActivated,
            this, &Window::openFileOfItem);
}
//===============================================
GQtUserShow::~GQtUserShow() {

}
//===============================================
