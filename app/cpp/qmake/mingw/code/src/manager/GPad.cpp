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
	createPad();

	QString lTitle = getPadItem("title");
	QString lLogo = getPadItem("logo");
	int lWidth = getPadItem("width").toInt();
	int lHeight = getPadItem("height").toInt();

	setWindowTitle(lTitle);
    setWindowIcon(QIcon(GRES("img", lLogo)));
	resize(lWidth, lHeight);
}
//===============================================
GPad::~GPad() {

}
//===============================================
void GPad::createDoms() {
	m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("xml", "pad.xml"));
    m_dom->createXPath();
}
//===============================================
int GPad::countPadItem() const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='pad']/map/data"));
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GPad::getPadItem(const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='pad']/%1").arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GPad::getPadItem(int _i, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='pad']/map/data[position()=%1]/%2").arg(_i + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GPad::countLoginItem() const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='login']/map/data"));
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GPad::getLoginItem(const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='login']/%1").arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GPad::getLoginItem(int _i, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='login']/map/data[position()=%1]/%2").arg(_i + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
void GPad::createPad() {
	QHBoxLayout* lHeaderLayout = new QHBoxLayout;
	lHeaderLayout->setMargin(0);
	lHeaderLayout->setSpacing(10);

	QVBoxLayout* lMainLayout = new QVBoxLayout;
	lMainLayout->addLayout(lHeaderLayout);
	lMainLayout->addStretch();
	lMainLayout->setMargin(10);
	lMainLayout->setSpacing(10);

	int lCount = countPadItem();
	QString lStyle = getPadItem("style");

	for(int i = 0; i < lCount; i++) {
		QString lCategory = getPadItem(i, "category");
		QString lType = getPadItem(i, "type");
		QString lKey = getPadItem(i, "key");
		QString lText = getPadItem(i, "text");
		QString lStyle = getPadItem(i, "style");
		QString lPicto = getPadItem(i, "picto");
		QString lPictoColor = getPadItem(i, "picto_color");
		int lPictoSize = getPadItem(i, "picto_size").toInt();

		QBoxLayout* lItemLayout = 0;
		if(lCategory == "header") {
			lItemLayout = lHeaderLayout;
		}
		else {
	        GLOG->addError(QString("Erreur la methode (createPad) a echoue\n"
	                "sur la categorie (%1).").arg(lCategory));
	        GLOG->showError(this);
	        continue;
	    }

		if(lType == "spacer") {
			lItemLayout->addStretch();
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
			lItemLayout->addWidget(lButton);
		}
	}

	setLayout(lMainLayout);
	setObjectName(lStyle);
}
//===============================================
QDialog* GPad::createLogin(QWidget* _parent) {
    QDialog* lMainPage = new QDialog(_parent);
	m_objectMap[lMainPage] = "login/dialog";

	QHBoxLayout* lUsernameLayout = new QHBoxLayout;
	lUsernameLayout->setMargin(0);
	lUsernameLayout->setSpacing(0);

	QHBoxLayout* lPasswordLayout = new QHBoxLayout;
	lPasswordLayout->setMargin(0);
	lPasswordLayout->setSpacing(0);

	QHBoxLayout* lButtonLayout = new QHBoxLayout;
	lButtonLayout->setMargin(0);
	lButtonLayout->setSpacing(10);

	QVBoxLayout* lMainLayout = new QVBoxLayout;
	lMainLayout->addLayout(lUsernameLayout);
	lMainLayout->addLayout(lPasswordLayout);
	lMainLayout->addLayout(lButtonLayout);
	lMainLayout->setMargin(10);
	lMainLayout->setSpacing(10);

	int lCount = countLoginItem();
	QString lTitle = getLoginItem("title");
	QString lLogo = getLoginItem("logo");
	int lWidth = getLoginItem("width").toInt();
	int lHeight = getLoginItem("height").toInt();
	int lLabelWidth = getLoginItem("label_width").toInt();

	for(int i = 0; i < lCount; i++) {
		QString lCategory = getLoginItem(i, "category");
		QString lType = getLoginItem(i, "type");
		QString lKey = getLoginItem(i, "key");
		QString lText = getLoginItem(i, "text");
		QString lStyle = getLoginItem(i, "style");
		QString lPicto = getLoginItem(i, "picto");
		QString lPictoColor = getLoginItem(i, "picto_color");
		int lPictoSize = getLoginItem(i, "picto_size").toInt();

		QBoxLayout* lItemLayout = 0;

		if(lCategory == "username") {
			lItemLayout = lUsernameLayout;
		}
		else if(lCategory == "password") {
			lItemLayout = lPasswordLayout;
		}
		else if(lCategory == "button") {
			lItemLayout = lButtonLayout;
		}
		else {
	        GLOG->addError(QString("Erreur la methode (createLogin) a echoue\n"
	                "sur la categorie (%1).").arg(lCategory));
	        GLOG->showError(this);
	        continue;
	    }

		if(lType == "spacer") {
			lItemLayout->addStretch();
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
			lItemLayout->addWidget(lButton);
		}
		else if(lType == "label") {
			QLabel* lLabel = new QLabel;
			lLabel->setText(lText);
			lLabel->setMinimumWidth(lLabelWidth);
			lItemLayout->addWidget(lLabel);
		}
		else if(lType == "label/icon") {
			QPushButton* lButton = new QPushButton;
			lButton->setObjectName("left");
			lButton->setText(lText);
			lButton->setMinimumWidth(lLabelWidth);
			if(lPicto != "" && lPictoColor != "") {
				lButton->setIcon(GPICTO(lPicto, lPictoColor));
			}
			if(lPictoSize != 0) {
				lButton->setIconSize(QSize(lPictoSize, lPictoSize));
			}
			lItemLayout->addWidget(lButton);
		}
		else if(lType == "lineedit") {
			QLineEdit* lLineEdit = new QLineEdit;
			if(lStyle != "") {
				lLineEdit->setObjectName("flat");
			}
			lItemLayout->addWidget(lLineEdit);
		}
	}

	lMainPage->setLayout(lMainLayout);

	lMainPage->setWindowTitle(lTitle);
	lMainPage->setWindowIcon(QIcon(GRES("img", lLogo)));
	lMainPage->resize(lWidth, lHeight);
	lMainPage->setFixedHeight(lMainPage->sizeHint().height());

    return lMainPage;
}
//===============================================
void GPad::onEvent() {
    QString lKey = m_objectMap[sender()];
    // pad/header
    if(lKey == "header/connect") {
    	QDialog* lDialog = createLogin();
    	lDialog->exec();
    }
    // login/connect
    else if(lKey == "login/connect") {
    	QDialog* lDialog = qobject_cast<QDialog*>(getObject("login/dialog"));
    	bool lLoginOn = true;
    	if(lLoginOn) {
    		lDialog->accept();
    		delete lDialog;
    	}

    }
    else {
    	GLOG->addError(QString("Erreur la methode (onEvent) a échoué\n"
    			"sur la clé (%1)").arg(lKey));
    }
    GLOG->showError(this);
}
//===============================================
