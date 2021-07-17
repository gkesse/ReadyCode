//===============================================
#include "GQtUserShow.h"
#include "GQtUserModel.h"
#include "GManager.h"
//===============================================
GQtUserShow::GQtUserShow(QWidget* parent) : 
GQtUi(parent) {    
    // table
    QTableView* lTableView = new QTableView;
    GQtUserModel* lModel = new GQtUserModel(lTableView);
    lTableView->setModel(lModel);
    
    QHBoxLayout* lTableViewLayout = new QHBoxLayout;
    lTableViewLayout->addWidget(lTableView);
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
