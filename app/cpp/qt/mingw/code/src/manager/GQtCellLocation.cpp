//===============================================
#include "GQtCellLocation.h"
#include "GQtXml.h"
#include "GQtLog.h"
//===============================================
GQtCellLocation::GQtCellLocation(QWidget* _parent) :
GQtDialog(_parent) {
    createDoms();

    QLabel* lCellLabel = new QLabel("Cellule :");
    m_cellEdit = new QLineEdit;
    QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
    m_cellEdit->setValidator(new QRegExpValidator(regExp, this));
    lCellLabel->setBuddy(m_cellEdit);
    QHBoxLayout* lTopLayout = new QHBoxLayout;
    lTopLayout->addWidget(lCellLabel);
    lTopLayout->addWidget(m_cellEdit);

    m_buttonBox = new QDialogButtonBox();
    m_buttonBox->addButton(QDialogButtonBox::Ok);
    m_buttonBox->addButton(QDialogButtonBox::Cancel);
    m_buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lTopLayout);
    lMainLayout->addWidget(m_buttonBox);

    setLayout(lMainLayout);
    setWindowTitle(getTitle());
    resize(getWidth(), getHeight());
    setFixedHeight(sizeHint().height());

    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(m_cellEdit, SIGNAL(textChanged(QString)), this, SLOT(onCellEdit(QString)));
}
//===============================================
GQtCellLocation::~GQtCellLocation() {

}
//===============================================
void GQtCellLocation::createDoms() {
    m_dom.reset(new GQtXml);
    m_dom->loadXmlFile(GQTRES("studio/xml", "spreadsheet.xml"));
}
//===============================================
QString GQtCellLocation::getTitle() const {
    m_dom->queryXPath("/rdv/celllocation/title/text");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GQtCellLocation::getWidth() const {
    m_dom->queryXPath("/rdv/celllocation/settings/width");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData.toInt();
}
//===============================================
int GQtCellLocation::getHeight() const {
    m_dom->queryXPath("/rdv/celllocation/settings/height");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData.toInt();
}
//===============================================
QString GQtCellLocation::getText() const {
    QString lData = m_cellEdit->text();
    return lData;
}
//===============================================
void GQtCellLocation::onCellEdit(const QString& _text) {
    m_buttonBox->button(QDialogButtonBox::Ok)->setEnabled(m_cellEdit->hasAcceptableInput());
}
//===============================================
