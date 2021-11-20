//===============================================
#include "GQtFindDialog.h"
#include "GQt.h"
#include "GLog.h"
//===============================================
GQtFindDialog::GQtFindDialog(QWidget* _parent) :
GQtDialog(_parent) {
    sGQt lParams;
    lParams.app_name = "ReadyApp | Recherche";
    GQt lTopLayout, lLeftLayout, lRightLayout, lMainLayout;
    GQt lFindLabel, lCloseButton;

    m_findEdit.createQLineEdit();
    lFindLabel.createQLabel("Recherche :");
    lFindLabel.setBuddy(m_findEdit);
    lTopLayout.createQHBoxLayout();
    lTopLayout.addWidget(lFindLabel);
    lTopLayout.addWidget(m_findEdit);

    m_caseCheckBox.createQCheckBox("Sensible à la casse");
    m_backwardCheckBox.createQCheckBox("Recherche arrière");
    lLeftLayout.createQVBoxLayout();
    lLeftLayout.addLayout(lTopLayout);
    lLeftLayout.addWidget(m_caseCheckBox);
    lLeftLayout.addWidget(m_backwardCheckBox);

    m_findButton.createQPushButton("Rechercher");
    m_findButton.setDefault(true);
    m_findButton.setEnabled(false);
    lCloseButton.createQPushButton("Quitter");
    lRightLayout.createQVBoxLayout();
    lRightLayout.addWidget(m_findButton);
    lRightLayout.addWidget(lCloseButton);
    lRightLayout.addStretch();

    lMainLayout.createQHBoxLayout();
    lMainLayout.addLayout(lLeftLayout);
    lMainLayout.addLayout(lRightLayout);
    lMainLayout.setLayout(this);

    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);
    setFixedHeight(sizeHint().height());

    m_findButton.connectObject(SIGNAL(clicked()), this, SLOT(onFindButton()));
    m_findEdit.connectObject(SIGNAL(textChanged(QString)), this, SLOT(onFindEdit(QString)));
    lCloseButton.connectObject(SIGNAL(clicked()), this, SLOT(close()));
}
//===============================================
GQtFindDialog::~GQtFindDialog() {

}
//===============================================
void GQtFindDialog::onFindButton() {
    GLOG->log(GMSG);
    QString lFindText = m_findEdit.getText();
    Qt::CaseSensitivity lCase = m_caseCheckBox.isChecked() ?
            Qt::CaseSensitive : Qt::CaseInsensitive;
    if(m_backwardCheckBox.isChecked()) {
        emit emitFindPrevious(lFindText, lCase);
    }
    else {
        emit emitFindNext(lFindText, lCase);
    }
}
//===============================================
void GQtFindDialog::onFindEdit(const QString& _text) {
    GLOG->log(GMSG);
    m_findButton.setEnabled(!m_findEdit.isEmpty());
}
//===============================================
