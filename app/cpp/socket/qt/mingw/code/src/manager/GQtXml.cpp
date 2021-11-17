//===============================================
#include <GQtXml.h>
#include "GManager.h"
//===============================================
GQtXml::GQtXml(QWidget* _parent) :
GWidget(_parent) {
    sGQt lParams;
    lParams.app_name = "ReadyApp | Interface XML";

    QTextEdit* lTextEdit = new QTextEdit;
    m_textEdit = lTextEdit;
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
GQtXml::~GQtXml() {

}
//===============================================
void GQtXml::onEvent() {
    QWidget* lWidget = qobject_cast<QWidget*>(sender());
    QString lWidgetId = m_widgetMap[lWidget];

    if(lWidgetId == "send") {
    	GManager lMgr;
    	if(lMgr.isEmpty(m_textEdit)) return;
    	std::string lDataIn, lDataOut;
    	lMgr.getData(m_textEdit, lDataIn);
    	lMgr.callServer(lDataIn, lDataOut);
    }
}
//===============================================
