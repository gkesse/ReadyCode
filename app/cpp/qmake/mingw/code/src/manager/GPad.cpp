//===============================================
#include "GPad.h"
#include "GPath.h"
#include "GXml.h"
#include "GStyle.h"
#include "GPicto.h"
#include "GLog.h"
//===============================================
GPad::GPad(QWidget* _parent) :
GWidget(_parent) {
	GSTYLE(GRES("css", "style.css"));
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
int GPad::countPadWindowItem() const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='pad/window']/map/data"));
    int lData = m_dom->countXPath();
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
int GPad::countPadHeaderItem() const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='pad/header']/map/data"));
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GPad::getPadHeaderItem(const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='pad/header']/%1").arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GPad::getPadHeaderItem(int _i, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='pad/header']/map/data[position()=%1]/%2").arg(_i + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
void GPad::createWindow() {
	QVBoxLayout* lMainLayout = new QVBoxLayout;
	lMainLayout->setMargin(10);
	lMainLayout->setSpacing(10);

	int lCount = countPadWindowItem();
	QString lStyle = getPadWindowItem("style");

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
	setObjectName(lStyle);
}
//===============================================
QWidget* GPad::createHeader() {
    QFrame* lMainPage = new QFrame;
	QHBoxLayout* lMainLayout = new QHBoxLayout;
	lMainLayout->setMargin(0);
	lMainLayout->setSpacing(10);

	int lCount = countPadHeaderItem();

	for(int i = 0; i < lCount; i++) {
		QString lType = getPadHeaderItem(i, "type");
		QString lKey = getPadHeaderItem(i, "key");
		QString lText = getPadHeaderItem(i, "text");
		QString lStyle = getPadHeaderItem(i, "style");
		QString lPicto = getPadHeaderItem(i, "picto");
		QString lPictoColor = getPadHeaderItem(i, "picto_color");
		int lPictoSize = getPadHeaderItem(i, "picto_size").toInt();

		if(lType == "spacer") {
			lMainLayout->addStretch();
		}
		else if(lType == "button") {
			QPushButton* lButton = new QPushButton;
			m_objectMap[lButton] = lKey;
			lButton->setObjectName(lStyle);
			lButton->setText(lText);
			lButton->setCursor(Qt::PointingHandCursor);
			if(lPicto != "" && lPictoColor != "") {
				lButton->setIcon(GPICTO(lPicto, lPictoColor));
			}
			if(lPictoSize != 0) {
				lButton->setIconSize(QSize(lPictoSize, lPictoSize));
			}
			connect(lButton, SIGNAL(clicked()), this, SLOT(onEvent()));
			lMainLayout->addWidget(lButton);
		}
	}

	lMainPage->setLayout(lMainLayout);
    return lMainPage;
}
//===============================================
void GPad::onEvent() {
    QString lKey = m_objectMap[sender()];
    if(lKey == "header/connect") {

    }
    else {
    	GLOG->addError(QString("Erreur la methode (onEvent) a échoué\n"
    			"sur la clé (%1)").arg(lKey));
    }
    GLOG->showError(this);
}
//===============================================
