//===============================================
#include "GPadMdiUi.h"
#include "GTitleBar.h"
#include "GPadMdi.h"
#include "GStyle.h"
#include "GPath.h"
#include "GFont.h"
//===============================================
GPadMdiUi::GPadMdiUi(QWidget* _parent)
: GWidget(_parent) {
    GFont lFont;
    lFont.loadFont();
    GSTYLE(GRES("css", "style.css"));
    createDoms();
    createLayout();
}
//===============================================
GPadMdiUi::~GPadMdiUi() {

}
//===============================================
void GPadMdiUi::createLayout() {
    GTitleBar* lTitleBar = new GTitleBar(this);
    lTitleBar->setObjectName("bottom");
    GPadMdi* lPadMdi = new GPadMdi;

    QVBoxLayout* lBodyLayout = new QVBoxLayout;
    lBodyLayout->addWidget(lPadMdi);
    lBodyLayout->setMargin(5);
    lBodyLayout->setSpacing(5);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(lTitleBar);
    lMainLayout->addLayout(lBodyLayout);
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(0);

    setLayout(lMainLayout);
    setObjectName("flat");

    m_sizeGrip = new QSizeGrip(this);
}
//===============================================
void GPadMdiUi::resizeEvent(QResizeEvent* event) {
    int lSize = 10;
    m_sizeGrip->move(width() - lSize, height() - lSize);
    m_sizeGrip->resize(lSize, lSize);
}
//===============================================
