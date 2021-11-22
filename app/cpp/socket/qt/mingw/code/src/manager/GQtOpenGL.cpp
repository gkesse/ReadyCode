//===============================================
#include "GQtOpenGL.h"
#include "GQt.h"
#include "GManager.h"
//===============================================
GQtOpenGL::GQtOpenGL(QWidget* _parent) :
GQtWidget(_parent) {
    sGQt lParams; GQt lQt;

    m_textEdit = lQt.createQTextEdit();
    QPushButton* lSendButton = new QPushButton("Envoyer");
    QVBoxLayout* lButtonLayout = new QVBoxLayout;
    lButtonLayout->addWidget(lSendButton);
    lButtonLayout->setAlignment(Qt::AlignTop);
    QHBoxLayout* lCenterLayout = new QHBoxLayout();
    lCenterLayout->addWidget(m_textEdit);
    lCenterLayout->addLayout(lButtonLayout);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lCenterLayout);

    setLayout(lMainLayout);
    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);

    connect(lSendButton, SIGNAL(clicked()), this, SLOT(onSendButton()));
}
//===============================================
GQtOpenGL::~GQtOpenGL() {

}
//===============================================
void GQtOpenGL::onSendButton() {
    GQt lQt; GManager lMgr;
    if(lQt.isEmpty(m_textEdit)) return;
    std::string lDataIn, lDataOut;
    lDataIn = m_textEdit->toPlainText().toStdString();
    lMgr.callServer(lDataIn, lDataOut);
}
//===============================================
