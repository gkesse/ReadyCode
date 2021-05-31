//================================================
#include "GWindow.h"
#include <QtAwesome.h>
//================================================
GWindow::GWindow(QWidget* parent) : QFrame(parent) {
    QtAwesome* awesome = new QtAwesome(this);
    awesome->initFontAwesome();

    QPushButton* lButton = new QPushButton;
    QVariantMap options;
    options.insert("anim", qVariantFromValue( new QtAwesomeAnimation(lButton) ) );
    lButton->setText("Button");
    lButton->setIcon(awesome->icon( fa::beer, options  ) );
    
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(lButton);
    lMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    
    setLayout(lMainLayout);
}
//================================================
GWindow::~GWindow() {
    
}
//================================================
