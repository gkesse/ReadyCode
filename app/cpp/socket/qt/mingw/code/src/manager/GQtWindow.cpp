//===============================================
#include "GQtWindow.h"
#include "GSocket.h"
#include "GXml.h"
#include "GDefine.h"
#include "GQt.h"
#include "GStruct.h"
//===============================================
GQtWindow::GQtWindow(QWidget* _parent) :
GQtWidget(_parent) {
    sGQt lParams;
    GQt lTextEdit, lSendButton, lButtonLayout, lCenterLayout, lMainLayout;

    lTextEdit.createQTextEdit();
    lSendButton.createQPushButton("Envoyer", "send", m_QWidgetMap);
    lButtonLayout.createQVBoxLayout();
    lButtonLayout.addWidget(lSendButton);
    lButtonLayout.setAlignment(Qt::AlignTop);
    lCenterLayout.createQHBoxLayout();
    lCenterLayout.addWidget(lTextEdit);
    lCenterLayout.addLayout(lButtonLayout);
    lMainLayout.createQVBoxLayout();
    lMainLayout.addLayout(lCenterLayout);
    lMainLayout.setLayout(this);
    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);
    lSendButton.connectObject(SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GQtWindow::~GQtWindow() {

}
//===============================================
