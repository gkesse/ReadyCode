//===============================================
#include "GQtSortDialog.h"
#include "GQtSortBox.h"
#include "GStruct.h"
#include "GQt.h"
#include "GQtLog.h"
//===============================================
GQtSortDialog::GQtSortDialog(QWidget* _parent) :
QDialog(_parent) {
    sGQt lParams; GQt lQt;
    lParams.app_name = "ReadyApp-Spreadsheet | Tri de cellule";
    lParams.height = 10;

    GQtSortBox* lPrimaryBox = new GQtSortBox;
    GQtSortBox* lSecondBox = new GQtSortBox;
    GQtSortBox* lThirdBox = new GQtSortBox;

    lSecondBox->hide();
    lThirdBox->hide();

    lSecondBox->setTitle("Clé secondaire");
    lThirdBox->setTitle("Clé tertiare");

    QPushButton* lOkButton = new QPushButton("OK");
    QPushButton* lCancelButton = new QPushButton("Annuler");
    QPushButton* lMoreButton = new QPushButton("Avancé");
    lMoreButton->setCheckable(true);
    QVBoxLayout* lRightLayout = new QVBoxLayout;
    lRightLayout->addWidget(lOkButton);
    lRightLayout->addWidget(lCancelButton);
    lQt.addSpacer(lRightLayout);
    lRightLayout->addWidget(lMoreButton);

    QGridLayout* lMainLayout = new QGridLayout;
    lMainLayout->addWidget(lPrimaryBox, 0, 0);
    lMainLayout->addLayout(lRightLayout, 0, 1, 2, 1);
    lQt.addVSpacer(lMainLayout, 1, 0);
    lMainLayout->addWidget(lSecondBox, 2, 0);
    lMainLayout->addWidget(lThirdBox, 3, 0);

    setLayout(lMainLayout);
    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);

    layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(lOkButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(lCancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(lMoreButton, SIGNAL(toggled(bool)), lSecondBox, SLOT(setVisible(bool)));
    connect(lMoreButton, SIGNAL(toggled(bool)), lThirdBox, SLOT(setVisible(bool)));
}
//===============================================
GQtSortDialog::~GQtSortDialog() {

}
//===============================================
void GQtSortDialog::onMoreButton() {
    GQTLOG->write(GMSG);
}
//===============================================
