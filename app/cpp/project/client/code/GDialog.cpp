//================================================
#include "GDialog.h"
//================================================
GDialog::GDialog(QWidget* parent) : QDialog(parent) {
    QLabel* lLabel = new QLabel;
    lLabel->setText("Voulez-vous continuer l'opération ?");

    QPushButton* lOk = new QPushButton;
    lOk->setText("Ok");

    QPushButton* lCancel = new QPushButton;
    lCancel->setText("Annuler");

    QHBoxLayout* lButtonLayout = new QHBoxLayout;
    lButtonLayout->addWidget(lCancel);
    lButtonLayout->addWidget(lOk);
    lButtonLayout->setAlignment(Qt::AlignRight);
    
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(lLabel, 1);
    lMainLayout->addLayout(lButtonLayout);
    
    setLayout(lMainLayout);
    
    setWindowTitle("ReadyApp");
    
    connect(lOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(lCancel, SIGNAL(clicked()), this, SLOT(reject()));
}
//================================================
GDialog::~GDialog() {
    
}
//================================================
