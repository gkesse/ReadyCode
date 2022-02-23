//===============================================
#include "GPad.h"
#include "GPath.h"
#include "GXml.h"
//===============================================
GPad::GPad(QWidget* _parent) :
GWidget(_parent) {
	createDoms();
	createWindow();

	QString lTitle = getPadItem("title");
	int lWidth = getPadItem("width").toInt();
	int lHeight = getPadItem("height").toInt();

	setWindowTitle(lTitle);
	resize(lWidth, lHeight);
}
//===============================================
GPad::~GPad() {

}
//===============================================
void GPad::createDoms() {
	m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("xml", "app.xml"));
    m_dom->createXPath();
}
//===============================================
QString GPad::getPadItem(const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='pad']/%1").arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GPad::getPadWindowItem(const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='pad/window']/%1").arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GPad::getPadWindowItem(int _i, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='pad/window']/map/data[position()=%1]/%2").arg(_i + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GPad::countPadWindowItem() const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='pad/window']/map/data"));
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
void GPad::createWindow() {
	QVBoxLayout* lMainLayout = new QVBoxLayout;
	lMainLayout->setMargin(0);
	lMainLayout->setSpacing(10);

	int lCount = countPadWindowItem();

	for(int i = 0; i < lCount; i++) {
		QString lType = getPadWindowItem(i, "type");

		if(lType == "spacer") {
			lMainLayout->addStretch();
		}
		else if(lType == "header") {
			lMainLayout->addWidget(createHeader());
		}
	}

	setLayout(lMainLayout);
}
//===============================================
QWidget* GPad::createHeader() {
    QFrame* lMainPage = new QFrame;
	QHBoxLayout* lMainLayout = new QHBoxLayout;
	lMainLayout->setMargin(0);
	lMainLayout->setSpacing(10);

	QPushButton* lButton = new QPushButton;
	lButton->setText("Connexion");
	lMainLayout->addWidget(lButton);

	lMainPage->setLayout(lMainLayout);
    return lMainPage;
}
//===============================================
