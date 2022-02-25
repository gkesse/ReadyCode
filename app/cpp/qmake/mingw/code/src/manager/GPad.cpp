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

	m_loginDialog = createLogin(this);

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
			addObject(lButton, lKey);
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
	addObject(lMainPage, "login/dialog");
	lMainPage->installEventFilter(this);

	QHBoxLayout* lUsernameLayout = new QHBoxLayout;
	lUsernameLayout->setMargin(0);
	lUsernameLayout->setSpacing(0);

	QHBoxLayout* lPasswordLayout = new QHBoxLayout;
	lPasswordLayout->setMargin(0);
	lPasswordLayout->setSpacing(0);

	QHBoxLayout* lMessageLayout = new QHBoxLayout;
	lMessageLayout->setMargin(0);
	lMessageLayout->setSpacing(0);

	QHBoxLayout* lButtonLayout = new QHBoxLayout;
	lButtonLayout->setMargin(0);
	lButtonLayout->setSpacing(10);

	QHBoxLayout* lAccountLayout = new QHBoxLayout;
	lAccountLayout->setMargin(0);
	lAccountLayout->setSpacing(10);

	QVBoxLayout* lMainLayout = new QVBoxLayout;
	lMainLayout->addLayout(lUsernameLayout);
	lMainLayout->addLayout(lPasswordLayout);
	lMainLayout->addLayout(lMessageLayout);
	lMainLayout->addLayout(lButtonLayout);
	lMainLayout->addLayout(lAccountLayout);
	lMainLayout->setMargin(10);
	lMainLayout->setSpacing(10);

	int lCount = countLoginItem();
	QString lTitle = getLoginItem("title");
	QString lLogo = getLoginItem("logo");
	int lWidth = getLoginItem("width").toInt();
	int lHeight = getLoginItem("height").toInt();
	int lLabelWidth = getLoginItem("label_width").toInt();
	bool lWidthFix = (getLoginItem("width_fix") == "1");
	bool lHeightFix = (getLoginItem("height_fix") == "1");

	for(int i = 0; i < lCount; i++) {
		QString lCategory = getLoginItem(i, "category");
		QString lType = getLoginItem(i, "type");
		QString lStyle = getLoginItem(i, "style");
		QString lAlign = getLoginItem(i, "align");
		QString lAction = getLoginItem(i, "action");
		QString lKey = getLoginItem(i, "key");
		QString lKeyClear = getLoginItem(i, "key_clear");
		QString lText = getLoginItem(i, "text");
		QString lEchoMode = getLoginItem(i, "echo_mode");
		QString lMask = getLoginItem(i, "mask");
		QString lPicto = getLoginItem(i, "picto");
		QString lPictoClear = getLoginItem(i, "picto_clear");
		QString lPictoColor = getLoginItem(i, "picto_color");
		int lPictoSize = getLoginItem(i, "picto_size").toInt();
		bool lLink = (getLoginItem(i, "link") == "1");

		QBoxLayout* lItemLayout = 0;

		if(lCategory == "username") {
			lItemLayout = lUsernameLayout;
		}
		else if(lCategory == "password") {
			lItemLayout = lPasswordLayout;
		}
		else if(lCategory == "message") {
			lItemLayout = lMessageLayout;
		}
		else if(lCategory == "button") {
			lItemLayout = lButtonLayout;
		}
		else if(lCategory == "account") {
			lItemLayout = lAccountLayout;
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
			addObject(lButton, lKey);
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
		else if(lType == "label/message") {
			QLabel* lLabel = new QLabel;
			addObject(lLabel, lKey);
			lLabel->setObjectName(lStyle);
			lLabel->setText(lText);
			if(lKey == "login/error") {
				lLabel->hide();
			}
			if(lAlign == "center") {
				lLabel->setAlignment(Qt::AlignCenter);
			}
			lLabel->setOpenExternalLinks(lLink);
			lItemLayout->addWidget(lLabel);
		}
		else if(lType == "label/icon") {
			QPushButton* lButton = new QPushButton;
			lButton->setObjectName(lStyle);
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
			lLineEdit->setObjectName(lStyle);
			addObject(lLineEdit, lKey);
			if(lEchoMode == "password") {
				lLineEdit->setEchoMode(QLineEdit::Password);
			}
			if(lMask != "") {
				lLineEdit->setInputMask(lMask);
			}
			lItemLayout->addWidget(lLineEdit);
		}
		else if(lType == "lineedit/icon") {
			QLineEdit* lLineEdit = new QLineEdit;
			lLineEdit->setObjectName(lStyle);
			addObject(lLineEdit, lKey);
			if(lText != "") {
				lLineEdit->setPlaceholderText(lText);
			}
			if(lEchoMode == "password") {
				lLineEdit->setEchoMode(QLineEdit::Password);
			}
			if(lMask != "") {
				lLineEdit->setInputMask(lMask);
			}
			QPushButton* lButton = new QPushButton(lLineEdit);
			if(lPicto != "" && lPictoColor != "") {
				lButton->setIcon(GPICTO(lPicto, lPictoColor));
			}
			if(lPictoSize != 0) {
				lButton->setIconSize(QSize(lPictoSize, lPictoSize));
			}
			lItemLayout->addWidget(lLineEdit);
		}
		else if(lType == "lineedit/icon/clear") {
			QLineEdit* lLineEdit = new QLineEdit;
			lLineEdit->setObjectName(lStyle);
			addObject(lLineEdit, lKey);
			if(lText != "") {
				lLineEdit->setPlaceholderText(lText);
			}
			if(lEchoMode == "password") {
				lLineEdit->setEchoMode(QLineEdit::Password);
			}
			if(lMask != "") {
				lLineEdit->setInputMask(lMask);
			}
			if(lPicto != "" && lPictoColor != "" && lPictoSize != 0) {
				QPushButton* lButton = new QPushButton(lLineEdit);
				lButton->setIcon(GPICTO(lPicto, lPictoColor));
				lButton->setIconSize(QSize(lPictoSize, lPictoSize));
			}
			if(lPictoClear != "" && lPictoColor != "" && lPictoSize != 0) {
				QPushButton* lButton = new QPushButton(lLineEdit);
				addObject(lButton, lKeyClear);
				lButton->setCursor(Qt::PointingHandCursor);
				lButton->setIcon(GPICTO(lPictoClear, lPictoColor));
				lButton->setIconSize(QSize(lPictoSize, lPictoSize));
				lButton->move(lWidth - 50, 0);
				lButton->hide();
				connect(lButton, SIGNAL(clicked()), this, SLOT(onEvent()));
			}
			connect(lLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onEvent(QString)));
			lItemLayout->addWidget(lLineEdit);
		}
	}

	lMainPage->setLayout(lMainLayout);

	lMainPage->setWindowTitle(lTitle);
	lMainPage->setWindowIcon(QIcon(GRES("img", lLogo)));
	lMainPage->resize(lWidth, lHeight);
	if(lWidthFix) {
		lMainPage->setFixedWidth(lWidth);
	}
	if(lHeightFix) {
		lMainPage->setFixedHeight(lMainPage->sizeHint().height());
	}

    return lMainPage;
}
//===============================================
void GPad::onEvent() {
    QString lKey = m_objectMap[sender()];
    // pad/header
    if(lKey == "header/connect") {
    	QDialog* lDialog = qobject_cast<QDialog*>(getObject("login/dialog"));
    	QLabel* lErrorLabel = qobject_cast<QLabel*>(getObject("login/error"));
		lErrorLabel->hide();
		lDialog->setFixedHeight(lDialog->sizeHint().height());
    	lDialog->exec();
    }
    // login/connect
    else if(lKey == "login/connect") {
    	QDialog* lDialog = qobject_cast<QDialog*>(getObject("login/dialog"));
    	QLineEdit* lUsernameEdit = qobject_cast<QLineEdit*>(getObject("login/username"));
    	QLineEdit* lPasswordEdit = qobject_cast<QLineEdit*>(getObject("login/password"));
    	QLabel* lErrorLabel = qobject_cast<QLabel*>(getObject("login/error"));

    	QString lUsername = lUsernameEdit->text();
    	QString lPassword = lPasswordEdit->text();

    	if(!lErrorLabel->isHidden()) {
			lErrorLabel->hide();
			lDialog->setFixedHeight(lDialog->sizeHint().height());
    	}

    	if(lUsername != "") {
    		if(lPassword != "") {
				bool lLoginOn = false;
				if(lLoginOn) {
					lDialog->accept();
				}
    		}
        	else {
        		lErrorLabel->setText("Le mot de passe est obligatoire.");
        		lErrorLabel->show();
        		lDialog->setFixedHeight(lDialog->sizeHint().height());
        	}
        }
    	else {
    		lErrorLabel->setText("Le nom d'utilisateur est obligatoire.");
    		lErrorLabel->show();
    		lDialog->setFixedHeight(lDialog->sizeHint().height());
    	}
    }
    // login/username/clear
    else if(lKey == "login/username/clear") {
    	QLineEdit* lUsernameEdit = qobject_cast<QLineEdit*>(getObject("login/username"));
    	lUsernameEdit->clear();
    }
    // login/password/clear
    else if(lKey == "login/password/clear") {
    	QLineEdit* lPasswordEdit = qobject_cast<QLineEdit*>(getObject("login/password"));
    	lPasswordEdit->clear();
    }
    // end
    else {
    	GLOG->addError(QString("Erreur la methode (onEvent) a échoué\n"
    			"sur la clé (%1)").arg(lKey));
    }
    GLOG->showError(this);
}
//===============================================
void GPad::onEvent(const QString& _text) {
	QString lKey = m_objectMap[sender()];
	// login
	if(lKey == "login/username") {
    	QPushButton* lUsernameClear = qobject_cast<QPushButton*>(getObject("login/username/clear"));
    	bool lVisible = (_text != "");
    	lUsernameClear->setVisible(lVisible);
	}
	else if(lKey == "login/password") {
    	QPushButton* lPasswordClear = qobject_cast<QPushButton*>(getObject("login/password/clear"));
    	bool lVisible = (_text != "");
    	lPasswordClear->setVisible(lVisible);
	}
}
//===============================================
bool GPad::eventFilter(QObject* _obj, QEvent* _event) {
	QDialog* lLoginDialog = qobject_cast<QDialog*>(getObject("login/dialog"));

	// login/dialog
    if (_obj == lLoginDialog && _event->type() == QEvent::Resize) {
    	QPushButton* lUsernameClear = qobject_cast<QPushButton*>(getObject("login/username/clear"));
    	QPushButton* lPasswordClear = qobject_cast<QPushButton*>(getObject("login/password/clear"));
    	int lWidth = lLoginDialog->width();
    	lUsernameClear->move(lWidth - 50, 0);
    	lPasswordClear->move(lWidth - 50, 0);
    	return true;
    }
    // end
    return QObject::eventFilter(_obj, _event);
}
//===============================================
bool GPad::hasErrors() const {
	return !m_errors.empty();
}
//===============================================
void GPad::addErrors(const QString& _errors) {
	m_errors.append(_errors);
}
//===============================================
QString GPad::getErrors() const {
	if(!hasErrors()) return "";
	QString lErrors = "";
	for(int i = 0; i < m_errors.size(); i++) {
		lErrors += m_errors.at(i);
	}
	return lErrors;
}
//===============================================
void GPad::clearErrors() {
	m_errors.clear();
}
//===============================================
