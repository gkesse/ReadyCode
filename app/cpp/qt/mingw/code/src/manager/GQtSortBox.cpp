//===============================================
#include "GQtSortBox.h"
//===============================================
GQtSortBox::GQtSortBox(QWidget* _parent) :
GQtWidget(_parent) {
    QLabel* lColumnLabel = new QLabel("Colonne :");

    m_columnCombo = new QComboBox;
    m_columnCombo->addItem("None");

    QLabel* lOrderLabel = new QLabel("Ordre :");

    m_orderCombo = new QComboBox;
    m_orderCombo->addItem("Croissant");
    m_orderCombo->addItem("Décroissant");

    QGridLayout* lBoxLayout = new QGridLayout;
    lBoxLayout->addWidget(lColumnLabel, 0, 0);
    lBoxLayout->addWidget(m_columnCombo, 0, 1);
    //GQT->addHSpacer(lBoxLayout, 0, 2);
    lBoxLayout->addWidget(lOrderLabel, 1, 0);
    lBoxLayout->addWidget(m_orderCombo, 1, 1, 1, 2);

    m_groupBox = new QGroupBox("Clé primaire");
    m_groupBox->setLayout(lBoxLayout);

    QGridLayout* lMainLayout = new QGridLayout;
    lMainLayout->addWidget(m_groupBox, 0, 0);
    lMainLayout->setMargin(0);
    setLayout(lMainLayout);
}
//===============================================
GQtSortBox::~GQtSortBox() {

}
//===============================================
void GQtSortBox::setTitle(const QString& _title) {
    m_groupBox->setTitle(_title);
}
//===============================================
void GQtSortBox::clearColumnCombo() {
    m_columnCombo->clear();
}
//===============================================
void GQtSortBox::addItemColumnCombo(const QString& _item) {
    m_columnCombo->addItem(_item);
}
//===============================================
int GQtSortBox::currentIndexColumnCombo() const {
    return m_columnCombo->currentIndex();
}
//===============================================
int GQtSortBox::currentIndexOrderCombo() const {
    return m_orderCombo->currentIndex();
}
//===============================================
