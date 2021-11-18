//===============================================
#include "GQtXml.h"
#include "GQt.h"
#include "GManager.h"
//===============================================
GQtXml::GQtXml(QWidget* _parent) :
GQtWidget(_parent) {
    sGQt lParams;
    GQt lSendButton, lButtonLayout, lCenterLayout, lMainLayout;

    m_textEdit.createQTextEdit();
    lSendButton.createQPushButton("Envoyer", "send", m_QWidgetMap);
    lButtonLayout.createQVBoxLayout();
    lButtonLayout.addWidget(lSendButton);
    lButtonLayout.setAlignment(Qt::AlignTop);
    lCenterLayout.createQHBoxLayout();
    lCenterLayout.addWidget(m_textEdit);
    lCenterLayout.addLayout(lButtonLayout);
    lMainLayout.createQVBoxLayout();
    lMainLayout.addLayout(lCenterLayout);
    lMainLayout.setLayout(this);
    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);
    lSendButton.connectObject(SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GQtXml::~GQtXml() {

}
//===============================================
void GQtXml::onEvent() {
    QWidget* lWidget = qobject_cast<QWidget*>(sender());
    QString lWidgetId = m_QWidgetMap[lWidget];

    if(lWidgetId == "send") {
    	if(m_textEdit.isEmptyQTextEdit()) return;
    	GManager lMgr; std::string lDataIn, lDataOut;
    	m_textEdit.getDataQTextEdit(lDataIn);
    	lMgr.callServer(lDataIn, lDataOut);
    }
}
//===============================================
