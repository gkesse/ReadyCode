//===============================================
#include "GQtFindDialog.h"
#include "GQt.h"
#include "GLog.h"
//===============================================
GQtFindDialog::GQtFindDialog(QWidget* _parent) :
GQtDialog(_parent) {
    sGQt lParams;
    lParams.app_name = "ReadyApp | Recherche";
    GQt lFindLabel, lFindEdit, lTopLayout;
    GQt lCaseCheckBox, lBackwardCheckBox;
    GQt lFindButton, lCloseButton;
    GQt lLeftLayout, lRightLayout, lMainLayout;

    lFindEdit.createQLineEdit();
    lFindLabel.createQLabel("Recherche :");
    lFindLabel.setBuddy(lFindEdit);
    lTopLayout.createQHBoxLayout();
    lTopLayout.addWidget(lFindLabel);
    lTopLayout.addWidget(lFindEdit);

    lCaseCheckBox.createQCheckBox("Sensible à la casse");
    lBackwardCheckBox.createQCheckBox("Recherche arrière");
    lLeftLayout.createQVBoxLayout();
    lLeftLayout.addLayout(lTopLayout);
    lLeftLayout.addWidget(lCaseCheckBox);
    lLeftLayout.addWidget(lBackwardCheckBox);

    lFindButton.createQPushButton("Rechercher");
    lCloseButton.createQPushButton("Quitter");
    lRightLayout.createQVBoxLayout();
    lRightLayout.addWidget(lFindButton);
    lRightLayout.addWidget(lCloseButton);
    lRightLayout.addStretch();

    lMainLayout.createQHBoxLayout();
    lMainLayout.addLayout(lLeftLayout);
    lMainLayout.addLayout(lRightLayout);
    lMainLayout.setLayout(this);

    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);
    setFixedHeight(sizeHint().height());

    lFindButton.connectObject(SIGNAL(clicked()), this, SLOT(onFindButton()));
    lFindEdit.connectObject(SIGNAL(textChanged(QString)), this, SLOT(onFindEdit(QString)));
    lCloseButton.connectObject(SIGNAL(clicked()), this, SLOT(close()));
}
//===============================================
GQtFindDialog::~GQtFindDialog() {

}
//===============================================
void GQtFindDialog::onFindButton() {
	GLOG->log(GMSG);
}
//===============================================
void GQtFindDialog::onFindEdit(const QString& _text) {
	GLOG->log(GMSG, "%s", _text.toStdString().c_str());
}
//===============================================
