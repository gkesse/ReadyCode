//===============================================
#include "GQtFindDialog.h"
#include "GQtLog.h"
#include "GQtXml.h"
//===============================================
GQtFindDialog::GQtFindDialog(QWidget* _parent) :
GQtDialog(_parent) {
    createDoms();

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
    setWindowTitle(getTitle());
    resize(getWidth(), getHeight());
    setFixedHeight(sizeHint().height());

    connect(m_findButton, SIGNAL(clicked()), this, SLOT(onFindButton()));
    connect(m_findEdit, SIGNAL(textChanged(QString)), this, SLOT(onFindEdit(QString)));
    connect(lCloseButton, SIGNAL(clicked()), this, SLOT(close()));
}
//===============================================
GQtFindDialog::~GQtFindDialog() {

}
//===============================================
void GQtFindDialog::createDoms() {
    m_dom.reset(new GQtXml);
    m_dom->loadXmlFile(GQTRES("studio/xml", "spreadsheet.xml"));
}
//===============================================
QString GQtFindDialog::getTitle() const {
    m_dom->queryXPath("/rdv/finddialog/title/text");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GQtFindDialog::getWidth() const {
    m_dom->queryXPath("/rdv/finddialog/settings/width");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData.toInt();
}
//===============================================
int GQtFindDialog::getHeight() const {
    m_dom->queryXPath("/rdv/finddialog/settings/height");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData.toInt();
}
//===============================================
void GQtFindDialog::onFindButton() {
    QString lFindText = m_findEdit->text();
    Qt::CaseSensitivity lCaseSensitivity = Qt::CaseInsensitive;
    if(m_caseCheckBox->isChecked()) {
        lCaseSensitivity = Qt::CaseSensitive;
    }
    if(m_backwardCheckBox->isChecked()) {
        emit findPrevious(lFindText, lCaseSensitivity);
    }
    else {
        emit findNext(lFindText, lCaseSensitivity);
    }
}
//===============================================
void GQtFindDialog::onFindEdit(const QString& _text) {
    m_findButton->setEnabled(!_text.isEmpty());
}
//===============================================
