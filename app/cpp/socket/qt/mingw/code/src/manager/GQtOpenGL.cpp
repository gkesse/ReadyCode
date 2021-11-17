//===============================================
#include <GQtOpenGL.h>
#include "GSocket.h"
#include "GXml.h"
#include "GDefine.h"
#include "GQt.h"
#include "GStruct.h"
//===============================================
GQtOpenGL::GQtOpenGL(QWidget* _parent) :
GWidget(_parent) {
    sGQt lParams;
    GQt lTextEdit, lSendButton, lButtonLayout, lCenterLayout, lMainLayout;

    lTextEdit.createTextEdit();
    lSendButton.createButton("Envoyer", "send");
    lButtonLayout.createVBoxLayout();
    lButtonLayout.addWidget(lSendButton);
    lButtonLayout.setAlignment(Qt::AlignTop);
    lCenterLayout.createHBoxLayout();
    lCenterLayout.addWidget(lTextEdit);
    lCenterLayout.addLayout(lButtonLayout);
    lMainLayout.createVBoxLayout();
    lMainLayout.addLayout(lCenterLayout);
    lMainLayout.setLayout(this);
    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);
    lSendButton.connectObject(SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GQtOpenGL::~GQtOpenGL() {

}
//===============================================
