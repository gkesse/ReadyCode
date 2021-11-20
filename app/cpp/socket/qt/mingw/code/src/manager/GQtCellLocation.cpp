//===============================================
#include "GQtCellLocation.h"
#include "GQt.h"
#include "GLog.h"
//===============================================
GQtCellLocation::GQtCellLocation(QWidget* _parent) :
GQtDialog(_parent) {
    sGQt lParams;
    lParams.app_name = "ReadyApp | Localisation de la cellule ";
    GQt lTopLayout, lBottomLayout, lMainLayout;
    GQt lCellLabel, lCancelButton;

    lCellLabel.createQLabel("Cellule :");
    m_cellEdit.createQLineEdit();
    m_cellEdit.setValidator("[A-Za-z][1-9][0-9]{0,2}", this);
    lCellLabel.setBuddy(m_cellEdit);
    lTopLayout.createQHBoxLayout();
    lTopLayout.addWidget(lCellLabel);
    lTopLayout.addWidget(m_cellEdit);

    m_okButton.createQPushButton("OK");
    lCancelButton.createQPushButton("Annuler");
    lBottomLayout.createQHBoxLayout();
    lBottomLayout.addWidget(lCellLabel);
    lBottomLayout.addWidget(m_cellEdit);

    lMainLayout.createQVBoxLayout();
    lMainLayout.addLayout(lTopLayout);
    lMainLayout.addLayout(lBottomLayout);
    lMainLayout.setLayout(this);

    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);
    setFixedHeight(sizeHint().height());

    m_okButton.connectObject(SIGNAL(clicked()), this, SLOT(onOkButton()));
    m_cellEdit.connectObject(SIGNAL(textChanged(QString)), this, SLOT(onCellEdit(QString)));
    lCancelButton.connectObject(SIGNAL(clicked()), this, SLOT(close()));
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
    m_okButton.setEnabled(m_cellEdit.hasAcceptableInput());
}
//===============================================
