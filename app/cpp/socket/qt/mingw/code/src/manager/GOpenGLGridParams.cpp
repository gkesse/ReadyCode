//===============================================
#include "GOpenGLGridParams.h"
#include "GSocket.h"
#include "GXml.h"
#include "GDefine.h"
#include "GStruct.h"
//===============================================
GOpenGLGridParams::GOpenGLGridParams(QWidget* _parent) :
GWidget(_parent) {
    sGQt lParams;

    QTextEdit* lTextEdit = new QTextEdit;
    lTextEdit->setStyleSheet(QString(""
            "QTextEdit {"
            "border:none;"
            "background-color:black;"
            "color:white;"
            "font-size:14px;"
            "}"));

    QPushButton* lSendButton = new QPushButton;
    lSendButton->setText("Envoyer");
    m_widgetMap[lSendButton] = "send";

    QVBoxLayout* lButtonLayout = new QVBoxLayout;
    lButtonLayout->addWidget(lSendButton);
    lButtonLayout->setAlignment(Qt::AlignTop);

    QHBoxLayout* lCenterLayout = new QHBoxLayout;
    lCenterLayout->addWidget(lTextEdit, 1);
    lCenterLayout->addLayout(lButtonLayout);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lCenterLayout);

    setLayout(lMainLayout);
    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);

    connect(lSendButton, SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GOpenGLGridParams::~GOpenGLGridParams() {

}
//===============================================
void GOpenGLGridParams::dataIn(std::string& _dataIn) {
    GXml lXml, lPoint;
    lXml.blank();
    lXml.doc();
    lXml.root(RDV_DATA_ROOT);
    lXml.child(lPoint, RDV_POINT_DATA);
    lPoint.childs(RDV_POINT_X, "1.0");
    lPoint.childs(RDV_POINT_Y, "1.0");
    lPoint.childs(RDV_POINT_Z, "0.0");
    lXml.toString(_dataIn, "UTF-8");
    lXml.print();
    lXml.free();
}
//===============================================
void GOpenGLGridParams::call(const std::string& _dataIn, std::string& _dataOut) {
    GSocket lClient;
    sGSocket lParams;
    lParams.address_ip = "127.0.0.1";
    lClient.call(lParams, _dataIn, _dataOut);
}
//===============================================
void GOpenGLGridParams::onEvent() {
    QWidget* lWidget = qobject_cast<QWidget*>(sender());
    QString lWidgetId = m_widgetMap[lWidget];

    if(lWidgetId == "send") {
    	std::string lDataIn, lDataOut;
    	dataIn(lDataIn);
    	call(lDataIn, lDataOut);
    }
}
//===============================================
