//===============================================
#include "GQtCellLocation.h"
#include "GQt.h"
#include "GLog.h"
//===============================================
GQtCellLocation::GQtCellLocation(QWidget* _parent) :
GQtDialog(_parent) {
    sGQt lParams; GQt lQt;
    lParams.app_name = "ReadyApp | Localisation de cellule";

    QLabel* lCellLabel = new QLabel("Cellule :");
    m_cellEdit = new QLineEdit;
    lQt.setValidator(m_cellEdit, "[A-Za-z][1-9][0-9]{0,2}", this);
    lCellLabel->setBuddy(m_cellEdit);
    QHBoxLayout* lTopLayout = new QHBoxLayout;
    lTopLayout->addWidget(lCellLabel);
    lTopLayout->addWidget(m_cellEdit);

    m_buttonBox = new QDialogButtonBox();
    m_buttonBox->addButton(QDialogButtonBox::Ok);
    m_buttonBox->addButton(QDialogButtonBox::Cancel);
    lQt.setEnabled(m_buttonBox, QDialogButtonBox::Ok, false);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lTopLayout);
    lMainLayout->addWidget(m_buttonBox);

    setLayout(lMainLayout);
    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);
    setFixedHeight(sizeHint().height());

    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(m_cellEdit, SIGNAL(textChanged(QString)), this, SLOT(onCellEdit(QString)));
}
//===============================================
GQtCellLocation::~GQtCellLocation() {

}
//===============================================
void GQtCellLocation::onCellEdit(const QString& _text) {
    GLOG->showMsg(GMSG); GQt lQt;
    lQt.setEnabled(m_buttonBox, QDialogButtonBox::Ok, m_cellEdit->hasAcceptableInput());
}
//===============================================
