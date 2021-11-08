//===============================================
#include "GOpenGLGridParams.h"
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
void GOpenGLGridParams::onEvent() {
	QWidget* lWidget = qobject_cast<QWidget*>(sender());
	QString lWidgetId = m_widgetMap[lWidget];
	qDebug() << lWidgetId;
	if(lWidgetId == "send") {

	}
}
//===============================================
