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

	QString lTitle = getItem("pad", "title");
	QString lLogo = getItem("pad", "logo");
	int lWidth = getItem("pad", "width").toInt();
	int lHeight = getItem("pad", "height").toInt();

	setWindowTitle(lTitle);
    setWindowIcon(QIcon(GRES("img", lLogo)));
	resize(lWidth, lHeight);

    m_loginDialog = createLogin(this);
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
void GPad::createPad() {
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(createHeader());
    lMainLayout->addStretch();
    lMainLayout->setMargin(10);
    lMainLayout->setSpacing(10);

    QString lStyle = getItem("pad", "style");

    setLayout(lMainLayout);
    setObjectName(lStyle);
}
//===============================================
QWidget* GPad::createHeader() {
    QFrame* lPage = new QFrame;

    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countItem("header");
    QString lStyle = getItem("header", "style");

    for(int i = 0; i < lCount; i++) {
        QString lType = getItem("header", "type", i);
        QString lKey = getItem("header", "key", i);
        QString lText = getItem("header", "text", i);
        QString lStyle = getItem("header", "style", i);
        QString lPicto = getItem("header", "picto", i);
        QString lPictoColor = getItem("header", "picto_color", i);
        int lPictoSize = getItem("header", "picto_size", i).toInt();

        if(lType == "spacer") {
            lMainLayout->addStretch();
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
            lMainLayout->addWidget(lButton);
        }
    }

    lPage->setLayout(lMainLayout);
    lPage->setObjectName(lStyle);
    return lPage;
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

	int lCount = countItem("login");
	QString lTitle = getItem("login", "title");
	QString lLogo = getItem("login", "logo");
	int lWidth = getItem("login", "width").toInt();
	int lHeight = getItem("login", "height").toInt();
	int lLabelWidth = getItem("login", "label_width").toInt();
	bool lWidthFix = (getItem("login", "width_fix") == "1");
	bool lHeightFix = (getItem("login", "height_fix") == "1");

	for(int i = 0; i < lCount; i++) {
		QString lCategory = getItem("login", "category", i);
		QString lType = getItem("login", "type", i);
		QString lStyle = getItem("login", "style", i);
		QString lAlign = getItem("login", "align", i);
		QString lAction = getItem("login", "action", i);
		QString lKey = getItem("login", "key", i);
		QString lKeyClear = getItem("login", "key_clear", i);
		QString lText = getItem("login", "text", i);
		QString lEchoMode = getItem("login", "echo_mode", i);
		QString lMask = getItem("login", "mask", i);
		QString lPicto = getItem("login", "picto", i);
		QString lPictoClear = getItem("login", "picto_clear", i);
		QString lPictoColor = getItem("login", "picto_color", i);
		int lPictoSize = getItem("login", "picto_size", i).toInt();
		bool lLink = (getItem("login", "link", i) == "1");

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
	        GERROR(eGERR, QString("Erreur la categorie n'existe pas.\n"
	                "- categorie : (%1)").arg(lCategory));
	        GERROR_SHOWG(eGERR);
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
    //===============================================
    // header
    //===============================================
    if(lKey == "header/connect") {
    	QDialog* lDialog = qobject_cast<QDialog*>(getObject("login/dialog"));
    	QLabel* lErrorLabel = qobject_cast<QLabel*>(getObject("login/error"));
		lErrorLabel->hide();
		lDialog->setFixedHeight(lDialog->sizeHint().height());
    	lDialog->exec();
    }
    //===============================================
    // login
    //===============================================
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
    //===============================================
    // end
    //===============================================
    else {
    	GERROR(eGERR, QString("Erreur la cle n'existe pas.\n"
    			"- cle : (%1)").arg(lKey));
    }
    GERROR_SHOWG(eGERR);
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
