//===============================================
#include "GPadMdiUi.h"
#include "GTitleBar.h"
#include "GPadMdi.h"
#include "GStyle.h"
#include "GPath.h"
#include "GFont.h"
//===============================================
GPadMdiUi::GPadMdiUi(QWidget* _parent) :
GWidget(_parent) {
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
    GPadMdi* lPadMdi = new GPadMdi;

    QVBoxLayout* lPadMdiLayout = new QVBoxLayout;
    lPadMdiLayout->addWidget(lPadMdi);
    lPadMdiLayout->setContentsMargins(10,  0,  10,  10);
    lPadMdiLayout->setSpacing(0);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(lTitleBar);
    lMainLayout->addLayout(lPadMdiLayout);
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(0);

    setLayout(lMainLayout);

    m_sizeGrip = new QSizeGrip(this);
}
//===============================================
void GPadMdiUi::resizeEvent(QResizeEvent* event) {
    int lSize = 10;
    m_sizeGrip->move(width() - lSize, height() - lSize);
    m_sizeGrip->resize(lSize, lSize);
}
//===============================================
