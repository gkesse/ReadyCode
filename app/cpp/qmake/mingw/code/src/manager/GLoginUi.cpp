//===============================================
#include "GLog.h"
#include "GLoginUi.h"
#include "GTitleBarDialog.h"
#include "GAccountUi.h"
#include "GPath.h"
#include "GPicto.h"
#include "GConnection.h"
//===============================================
GLoginUi::GLoginUi(GConnection* _connection, QWidget* _parent)
: GDialog(_parent)
, m_connection(_connection) {
    createDoms();
    createLayout();
}
//===============================================
GLoginUi::~GLoginUi() {

}
//===============================================
void GLoginUi::createLayout() {
    new GTitleBarDialog(this);

    QHBoxLayout* lUsernameLayout = new QHBoxLayout;
    lUsernameLayout->setContentsMargins(0, 0, 0, 0);
    lUsernameLayout->setSpacing(0);

    QHBoxLayout* lPasswordLayout = new QHBoxLayout;
    lPasswordLayout->setContentsMargins(0, 0, 0, 0);
    lPasswordLayout->setSpacing(0);

    QHBoxLayout* lButtonLayout = new QHBoxLayout;
    lButtonLayout->setContentsMargins(0, 0, 0, 0);
    lButtonLayout->setSpacing(10);

    QHBoxLayout* lAccountLayout = new QHBoxLayout;
    lAccountLayout->setContentsMargins(0, 0, 0, 0);
    lAccountLayout->setSpacing(10);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lUsernameLayout);
    lMainLayout->addLayout(lPasswordLayout);
    lMainLayout->addLayout(lButtonLayout);
    lMainLayout->addLayout(lAccountLayout);
    lMainLayout->setContentsMargins(10, 10, 10, 10);
    lMainLayout->setSpacing(10);

    int lCount = countItem("login");
    QString lTitle = getItem("login", "title");
    QString lLogo = getItem("login", "logo");
    int lWidth = getItem("login", "width").toInt();
    int lHeight = getItem("login", "height").toInt();
    int lLabelWidth = getItem("login", "label_width").toInt();
    bool lWidthFix = (getItem("login", "width_fix_on") == "1");
    bool lHeightFix = (getItem("login", "height_fix_on") == "1");
    QString lStyle = getItem("login", "style");

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
        else if(lCategory == "account") {
            lItemLayout = lAccountLayout;
        }
        else {
            onErrorCategory(lCategory);
            GERROR_SHOWG2(eGERR);
            continue;
        }

        if(lType == "spacer") {
            lItemLayout->addStretch();
        }
        else if(lType == "button") {
            QPushButton* lButton = new QPushButton;
            addObj(lKey, lButton);
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
            addObj(lKey, lLineEdit);
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
            addObj(lKey, lLineEdit);
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
            lButton->move(5, 5);
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
            addObj(lKey, lLineEdit);
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
                lButton->move(5, 5);
                lButton->setIcon(GPICTO(lPicto, lPictoColor));
                lButton->setIconSize(QSize(lPictoSize, lPictoSize));
            }
            if(lPictoClear != "" && lPictoColor != "" && lPictoSize != 0) {
                QPushButton* lButton = new QPushButton(lLineEdit);
                addObj(lKeyClear, lButton);
                lButton->setCursor(Qt::PointingHandCursor);
                lButton->setIcon(GPICTO(lPictoClear, lPictoColor));
                lButton->setIconSize(QSize(lPictoSize, lPictoSize));
                lButton->move(lWidth - 50, 5);
                lButton->hide();
                connect(lButton, SIGNAL(clicked()), this, SLOT(onEvent()));
            }
            connect(lLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onEvent(QString)));
            lItemLayout->addWidget(lLineEdit);
        }
        else {
            onErrorType(lCategory, lType);
            GERROR_SHOWG2(eGERR);
            continue;
        }
    }

    setLayout(lMainLayout);
    resize(lWidth, lHeight);
    setObjectName(lStyle);
    setWindowTitle(lTitle);

    if(lWidthFix) {
        setFixedWidth(lWidth);
    }
    if(lHeightFix) {
        setFixedHeight(sizeHint().height());
    }
}
//===============================================
void GLoginUi::onEvent() {
    QString lKey = getKey(sender());
    //
    if(lKey == "login/connect") {
        onConnect();
    }
    else if(lKey == "login/username/clear") {
        onUsernameClear();
    }
    else if(lKey == "login/password/clear") {
        onPasswordClear();
    }
    else if(lKey == "login/account/create") {
        onAccountCreate();
    }
    else {
        onErrorKey(lKey);
    }
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GLoginUi::onEvent(const QString& _text) {
    QString lKey = getKey(sender());
    //
    if(lKey == "login/username") {
        onUsernameClear(_text);
    }
    else if(lKey == "login/password") {
        onPasswordClear(_text);
    }
    else {
        onErrorKey(lKey);
    }
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GLoginUi::onConnect() {
    QLineEdit* lUsernameEdit = (QLineEdit*)getObj("login/username");
    QLineEdit* lPasswordEdit = (QLineEdit*)getObj("login/password");

    QString lUsername = lUsernameEdit->text();
    QString lPassword = lPasswordEdit->text();

    if(lUsername == "") {
        GERROR_ADD(eGERR, "Le nom d'utilisateur est obligatoire.");
    }
    else if(lPassword == "") {
        GERROR_ADD(eGERR, "Le mot de passe est obligatoire.");
    }
    else {
        m_connection->setPseudo(lUsername);
        m_connection->setPassword(lPassword);
        m_connection->runConnection();

        if(m_connection->isConnect()) {
            accept();
        }
    }
}
//===============================================
void GLoginUi::onUsernameClear() {
    QLineEdit* lUsernameEdit = (QLineEdit*)getObj("login/username");
    lUsernameEdit->clear();
}
//===============================================
void GLoginUi::onUsernameClear(const QString& _text) {
    QPushButton* lUsernameClear = (QPushButton*)getObj("login/username/clear");
    bool lVisible = (_text != "");
    lUsernameClear->setVisible(lVisible);
}
//===============================================
void GLoginUi::onPasswordClear() {
    QLineEdit* lPasswordEdit = (QLineEdit*)getObj("login/password");
    lPasswordEdit->clear();
}
//===============================================
void GLoginUi::onPasswordClear(const QString& _text) {
    QPushButton* lPasswordClear = (QPushButton*)getObj("login/password/clear");
    bool lVisible = (_text != "");
    lPasswordClear->setVisible(lVisible);
}
//===============================================
void GLoginUi::onAccountCreate() {
    GAccountUi* lAccountUi = new GAccountUi(this);
    lAccountUi->exec();
}
//===============================================
