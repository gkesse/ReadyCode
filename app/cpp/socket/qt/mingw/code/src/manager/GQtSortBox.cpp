//===============================================
#include "GQtSortBox.h"
#include "GQt.h"
#include "GLog.h"
//===============================================
GQtSortBox::GQtSortBox(QWidget* _parent) :
GQtWidget(_parent) {
    GQt lQt;
    QLabel* lColumnLabel = new QLabel("Colonne :");
    QComboBox* lColumnCombo = new QComboBox;
    lColumnCombo->addItem("None");
    QLabel* lOrderLabel = new QLabel("Ordre :");
    QComboBox* lOrderCombo = new QComboBox;
    lOrderCombo->addItem("Croissant");
    lOrderCombo->addItem("Décroissant");
    QGridLayout* lBoxLayout = new QGridLayout;
    lBoxLayout->addWidget(lColumnLabel, 0, 0);
    lBoxLayout->addWidget(lColumnCombo, 0, 1);
    lQt.addHSpacer(lBoxLayout, 0, 2);
    lBoxLayout->addWidget(lOrderLabel, 1, 0);
    lBoxLayout->addWidget(lOrderCombo, 1, 1, 1, 2);
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
