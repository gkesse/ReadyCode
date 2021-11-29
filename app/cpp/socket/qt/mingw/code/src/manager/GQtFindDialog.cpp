//===============================================
#include "GQtFindDialog.h"
#include "GQt.h"
#include "GLog.h"
//===============================================
GQtFindDialog::GQtFindDialog(QWidget* _parent) :
GQtDialog(_parent) {
    sGQt lParams;
    lParams.app_name = "ReadyApp | Recherche de texte";

    m_findEdit = new QLineEdit;
    QLabel* lFindLabel = new QLabel("Recherche :");
    lFindLabel->setBuddy(m_findEdit);
    QHBoxLayout* lTopLayout = new QHBoxLayout;
    lTopLayout->addWidget(lFindLabel);
    lTopLayout->addWidget(m_findEdit);

    m_caseCheckBox = new QCheckBox("Sensible à la casse");
    m_backwardCheckBox = new QCheckBox("Recherche arrière");
    QVBoxLayout* lLeftLayout = new QVBoxLayout;
    lLeftLayout->addLayout(lTopLayout);
    lLeftLayout->addWidget(m_caseCheckBox);
    lLeftLayout->addWidget(m_backwardCheckBox);

    m_findButton = new QPushButton("Rechercher");
    m_findButton->setDefault(true);
    m_findButton->setEnabled(false);
    QPushButton* lCloseButton = new QPushButton("Quitter");
    QVBoxLayout* lRightLayout = new QVBoxLayout;
    lRightLayout->addWidget(m_findButton);
    lRightLayout->addWidget(lCloseButton);
    lRightLayout->addStretch();

    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->addLayout(lLeftLayout);
    lMainLayout->addLayout(lRightLayout);

    setLayout(lMainLayout);
    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);
    setFixedHeight(sizeHint().height());

    connect(m_findButton, SIGNAL(clicked()), this, SLOT(onFindButton()));
    connect(m_findEdit, SIGNAL(textChanged(QString)), this, SLOT(onFindEdit(QString)));
    connect(lCloseButton, SIGNAL(clicked()), this, SLOT(close()));
}
//===============================================
GQtFindDialog::~GQtFindDialog() {

}
//===============================================
void GQtFindDialog::onFindButton() {
    GLOG->showMsg(GMSG); GQt lQt;
    QString lFindText = m_findEdit->text();
    Qt::CaseSensitivity lCaseSensitivity = lQt.getCaseSensitivity(m_caseCheckBox);
    if(m_backwardCheckBox->isChecked()) {
        emit emitFindPrevious(lFindText, lCaseSensitivity);
    }
    else {
        emit emitFindNext(lFindText, lCaseSensitivity);
    }
}
//===============================================
void GQtFindDialog::onFindEdit(const QString& _text) {
    GLOG->showMsg(GMSG); GQt lQt;
    m_findButton->setEnabled(!lQt.isEmpty(m_findEdit));
}
//===============================================
