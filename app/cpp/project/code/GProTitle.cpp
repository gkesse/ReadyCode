//===============================================
#include "GProTitle.h"
#include "GManager.h"
#include "GSQLite.h"
//===============================================
GProTitle::GProTitle(QWidget* parent) :
GProUi(parent) {
	// title
	QPushButton* lTitle = new QPushButton;
	m_title = lTitle;
	lTitle->setText("TITLE");
	m_widgetMap[lTitle] = "title";

	// layout
	QHBoxLayout* lMainLayout = new  QHBoxLayout;
	lMainLayout->addWidget(lTitle);
	lMainLayout->setMargin(0);
	lMainLayout->setSpacing(0);

	setLayout(lMainLayout);

	connect(lTitle, SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GProTitle::~GProTitle() {

}
//===============================================
void GProTitle::setTitle(const QString& text) {
	m_title->setText(text);
}
//===============================================
void GProTitle::onEvent() {
	QWidget* lWidget = qobject_cast<QWidget*>(sender());
	QString lWidgetId = m_widgetMap[lWidget];
	onEvent(lWidgetId);
}
//===============================================
void GProTitle::onEvent(const QString& text) {
	qDebug() << text;
}
//===============================================
