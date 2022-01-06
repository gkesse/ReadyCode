//===============================================
#include "GQtSortDialog.h"
#include "GQtSortBox.h"
#include "GQtXml.h"
#include "GQtLog.h"
//===============================================
GQtSortDialog::GQtSortDialog(QWidget* _parent) :
GQtDialog(_parent) {
    primarySortBox = new GQtSortBox;
    secondarySortBox = new GQtSortBox;
    tertiarySortBox = new GQtSortBox;

    secondarySortBox->hide();
    tertiarySortBox->hide();

    secondarySortBox->setTitle("Clé secondaire");
    tertiarySortBox->setTitle("Clé tertiare");

    QPushButton* lOkButton = new QPushButton("OK");
    QPushButton* lCancelButton = new QPushButton("Annuler");
    QPushButton* lMoreButton = new QPushButton("Avancé");
    lMoreButton->setCheckable(true);
    QVBoxLayout* lRightLayout = new QVBoxLayout;
    lRightLayout->addWidget(lOkButton);
    lRightLayout->addWidget(lCancelButton);
    //lQt.addSpacer(lRightLayout);
    lRightLayout->addWidget(lMoreButton);

    QGridLayout* lMainLayout = new QGridLayout;
    lMainLayout->addWidget(primarySortBox, 0, 0);
    lMainLayout->addLayout(lRightLayout, 0, 1, 2, 1);
    //lQt.addVSpacer(lMainLayout, 1, 0);
    lMainLayout->addWidget(secondarySortBox, 2, 0);
    lMainLayout->addWidget(tertiarySortBox, 3, 0);

    setLayout(lMainLayout);
    setWindowTitle(getTitle());
    resize(getWidth(), getHeight());

    layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(lOkButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(lCancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(lMoreButton, SIGNAL(toggled(bool)), secondarySortBox, SLOT(setVisible(bool)));
    connect(lMoreButton, SIGNAL(toggled(bool)), tertiarySortBox, SLOT(setVisible(bool)));
}
//===============================================
GQtSortDialog::~GQtSortDialog() {

}
//===============================================
void GQtSortDialog::createDoms() {
    m_dom.reset(new GQtXml);
    m_dom->loadXmlFile(GQTRES("studio/xml", "spreadsheet.xml"));
}
//===============================================
QString GQtSortDialog::getTitle() const {
    m_dom->getRoot("rdv").getNode("celllocation");
    m_dom->getNode("title").getNode("text");
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GQtSortDialog::getWidth() const {
    m_dom->getRoot("rdv").getNode("celllocation");
    m_dom->getNode("settings").getNode("width");
    int lData = m_dom->getNodeValue().toInt();
    return lData;
}
//===============================================
int GQtSortDialog::getHeight() const {
    m_dom->getRoot("rdv").getNode("celllocation");
    m_dom->getNode("settings").getNode("height");
    int lData = m_dom->getNodeValue().toInt();
    return lData;
}
//===============================================
void GQtSortDialog::setColumnRange(QChar first, QChar last) {
    primarySortBox->clearColumnCombo();
    secondarySortBox->clearColumnCombo();
    tertiarySortBox->clearColumnCombo();

    secondarySortBox->addItemColumnCombo("None");
    tertiarySortBox->addItemColumnCombo("None");

    //primarySortBox->setMinimumSize(secondarySortBox->sizeHint());

    QChar ch = first;
    while (ch <= last) {
        primarySortBox->addItemColumnCombo(QString(ch));
        secondarySortBox->addItemColumnCombo(QString(ch));
        tertiarySortBox->addItemColumnCombo(QString(ch));
        ch = ch.unicode() + 1;
    }
}
//===============================================
int GQtSortDialog::currentIndexColumnCombo(int _index) const {
    int lCurrentIndex = 0;
    if(_index == 1) {
        lCurrentIndex = primarySortBox->currentIndexColumnCombo();
    }
    else if(_index == 2) {
        lCurrentIndex = secondarySortBox->currentIndexColumnCombo();
    }
    else if(_index == 3) {
        lCurrentIndex = tertiarySortBox->currentIndexColumnCombo();
    }
    return lCurrentIndex;
}
//===============================================
int GQtSortDialog::currentIndexOrderCombo(int _index) const {
    int lCurrentIndex = 0;
    if(_index == 1) {
        lCurrentIndex = primarySortBox->currentIndexOrderCombo();
    }
    else if(_index == 2) {
        lCurrentIndex = secondarySortBox->currentIndexOrderCombo();
    }
    else if(_index == 3) {
        lCurrentIndex = tertiarySortBox->currentIndexOrderCombo();
    }
    return lCurrentIndex;
}
//===============================================
void GQtSortDialog::onMoreButton() {

}
//===============================================
