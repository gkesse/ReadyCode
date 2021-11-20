//===============================================
#include "GQtCellLocation.h"
#include "GQt.h"
#include "GLog.h"
//===============================================
GQtCellLocation::GQtCellLocation(QWidget* _parent) :
GQtDialog(_parent) {
    sGQt lParams;
    lParams.app_name = "ReadyApp | Localisation de la cellule ";
    GQt lTopLayout, lMainLayout;
    GQt lCellLabel;

    lCellLabel.createQLabel("Cellule :");
    m_cellEdit.createQLineEdit();
    m_cellEdit.setValidator("[A-Za-z][1-9][0-9]{0,2}", this);
    lCellLabel.setBuddy(m_cellEdit);
    lTopLayout.createQHBoxLayout();
    lTopLayout.addWidget(lCellLabel);
    lTopLayout.addWidget(m_cellEdit);

    m_buttonBox.createQDialogButtonBox();
    m_buttonBox.addButton(QDialogButtonBox::Ok);
    m_buttonBox.addButton(QDialogButtonBox::Cancel);
    m_buttonBox.setEnabled(QDialogButtonBox::Ok, false);

    lMainLayout.createQVBoxLayout();
    lMainLayout.addLayout(lTopLayout);
    lMainLayout.addWidget(m_buttonBox);
    lMainLayout.setLayout(this);

    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);
    setFixedHeight(sizeHint().height());

    m_buttonBox.connectObject(SIGNAL(accepted()), this, SLOT(accept()));
    m_buttonBox.connectObject(SIGNAL(rejected()), this, SLOT(reject()));
    m_cellEdit.connectObject(SIGNAL(textChanged(QString)), this, SLOT(onCellEdit(QString)));
}
//===============================================
GQtCellLocation::~GQtCellLocation() {

}
//===============================================
void GQtCellLocation::onOkButton() {
    GLOG->log(GMSG);
    QString lCellText = m_cellEdit.getText();
}
//===============================================
void GQtCellLocation::onCellEdit(const QString& _text) {
    GLOG->log(GMSG);
    m_buttonBox.setEnabled(QDialogButtonBox::Ok, m_cellEdit);
}
//===============================================
