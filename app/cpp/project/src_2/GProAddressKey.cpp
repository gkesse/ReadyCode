//===============================================
#include "GProAddressKey.h"
#include "GManager.h"
//===============================================
GProAddressKey::GProAddressKey(QWidget* parent) :
GProUi(parent) {
	// layout
	QHBoxLayout* lMainLayout = new QHBoxLayout;
	m_mainLayout = lMainLayout;
	lMainLayout->setAlignment(Qt::AlignLeft);
	lMainLayout->setMargin(0);
	lMainLayout->setSpacing(0);

	setLayout(lMainLayout);
}
//===============================================
GProAddressKey::~GProAddressKey() {

}
//===============================================
void GProAddressKey::setAddress(const QString& text) {
	QStringList lMap = text.split("/");
	QString lKey = "";

	GManager::Instance()->clearLayout(m_mainLayout);

	for(int i = 0; i < lMap.size(); i++) {
		if(i != 0) {
			QPushButton* lSep = new QPushButton;
			lSep->setText(">");
			lSep->setStyleSheet("text-align:center;border:none;padding:5px;");
			m_mainLayout->addWidget(lSep);
		}

		if(i != 0) {lKey += "/";}
		lKey += lMap[i];

		QPushButton* lButton = new QPushButton;
		lButton->setText(lMap[i]);
		lButton->setCursor(Qt::PointingHandCursor);
		lButton->setStyleSheet("text-align:center;padding:5px;");
		m_widgetMap[lButton] = lKey;
		m_mainLayout->addWidget(lButton);
		connect(lButton, SIGNAL(clicked()), this, SLOT(onEvent()));
	}
}
//===============================================
void GProAddressKey::onEvent() {
	QWidget* lWidget = qobject_cast<QWidget*>(sender());
	QString lWidgetId = m_widgetMap[lWidget];
	GManager::Instance()->setPage(lWidgetId);
}
//===============================================
