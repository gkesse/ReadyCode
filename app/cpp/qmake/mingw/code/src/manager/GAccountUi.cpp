//===============================================
#include "GAccountUi.h"
#include "GTitleBarDialog.h"
#include "GPath.h"
#include "GXml.h"
#include "GPicto.h"
#include "GLog.h"
#include "GUser.h"
//===============================================
GAccountUi::GAccountUi(QWidget* _parent)
: GDialog(_parent) {
    createDoms();
    createLayout();
}
//===============================================
GAccountUi::~GAccountUi() {

}
//===============================================
void GAccountUi::createLayout() {
    new GTitleBarDialog(this);

    QHBoxLayout* lUsernameLayout = new QHBoxLayout;
    lUsernameLayout->setMargin(0);
    lUsernameLayout->setSpacing(0);

    QHBoxLayout* lPasswordLayout = new QHBoxLayout;
    lPasswordLayout->setMargin(0);
    lPasswordLayout->setSpacing(0);

    QHBoxLayout* lConfirmLayout = new QHBoxLayout;
    lPasswordLayout->setMargin(0);
    lPasswordLayout->setSpacing(0);

    QHBoxLayout* lButtonLayout = new QHBoxLayout;
    lButtonLayout->setMargin(0);
    lButtonLayout->setSpacing(10);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lUsernameLayout);
    lMainLayout->addLayout(lPasswordLayout);
    lMainLayout->addLayout(lConfirmLayout);
    lMainLayout->addLayout(lButtonLayout);
    lMainLayout->setMargin(10);
    lMainLayout->setSpacing(10);

    int lCount = countItem("account");
    QString lTitle = getItem("account", "title");
    QString lLogo = getItem("account", "logo");
    int lWidth = getItem("account", "width").toInt();
    int lHeight = getItem("account", "height").toInt();
    int lLabelWidth = getItem("account", "label_width").toInt();
    bool lWidthFix = (getItem("account", "width_fix_on") == "1");
    bool lHeightFix = (getItem("account", "height_fix_on") == "1");
    QString lStyle = getItem("account", "style");

    for(int i = 0; i < lCount; i++) {
        QString lCategory = getItem("account", "category", i);
        QString lType = getItem("account", "type", i);
        QString lStyle = getItem("account", "style", i);
        QString lAlign = getItem("account", "align", i);
        QString lAction = getItem("account", "action", i);
        QString lKey = getItem("account", "key", i);
        QString lKeyClear = getItem("account", "key_clear", i);
        QString lText = getItem("account", "text", i);
        QString lEchoMode = getItem("account", "echo_mode", i);
        QString lMask = getItem("account", "mask", i);
        QString lPicto = getItem("account", "picto", i);
        QString lPictoClear = getItem("account", "picto_clear", i);
        QString lPictoColor = getItem("account", "picto_color", i);
        int lPictoSize = getItem("account", "picto_size", i).toInt();

        QBoxLayout* lItemLayout = 0;

        if(lCategory == "username") {
            lItemLayout = lUsernameLayout;
        }
        else if(lCategory == "password") {
            lItemLayout = lPasswordLayout;
        }
        else if(lCategory == "confirm") {
            lItemLayout = lConfirmLayout;
        }
        else if(lCategory == "button") {
            lItemLayout = lButtonLayout;
        }
        else {
            onErrorCategory(lCategory);
            GERROR_SHOWG(eGERR);
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
            GERROR_SHOWG(eGERR);
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
void GAccountUi::onEvent() {
    QString lKey = getKey(sender());
    //
    if(lKey == "account/create") {
        onAccountCreate();
    }
    else if(lKey == "account/username/clear") {
        onUsernameClear();
    }
    else if(lKey == "account/password/clear") {
        onPasswordClear();
    }
    else if(lKey == "account/confirm/clear") {
        onConfirmClear();
    }
    else {
        onErrorKey(lKey);
    }
    GERROR_SHOWG(eGERR);
}
//===============================================
void GAccountUi::onEvent(const QString& _text) {
    QString lKey = getKey(sender());
    //
    if(lKey == "account/username") {
        onUsernameClear(_text);
    }
    else if(lKey == "account/password") {
        onPasswordClear(_text);
    }
    else if(lKey == "account/confirm") {
        onConfirmClear(_text);
    }
    else {
        onErrorKey(lKey);
    }
    GERROR_SHOWG(eGERR);
}
//===============================================
void GAccountUi::onAccountCreate() {
    QLineEdit* lUsernameEdit = (QLineEdit*)getObj("account/username");
    QLineEdit* lPasswordEdit = (QLineEdit*)getObj("account/password");
    QLineEdit* lConfirmEdit = (QLineEdit*)getObj("account/confirm");

    QString lUsername = lUsernameEdit->text();
    QString lPassword = lPasswordEdit->text();
    QString lConfirm = lConfirmEdit->text();

    if(lUsername == "") {
        GERROR(eGERR, "Le nom d'utilisateur est obligatoire.");
    }
    else if(lPassword == "") {
        GERROR(eGERR, "Le mot de passe est obligatoire.");
    }
    else if(lConfirm == "") {
        GERROR(eGERR, "La confirmation est obligatoire.");
    }
    else if(lConfirm != lPassword) {
        GERROR(eGERR, "La confirmation est différente du mot de passe.");
    }
    else {
        GUser lUser;
        lUser.setPseudo(lUsername);
        lUser.setPassword(lPassword);

        if(lUser.createAccount()) {
            accept();
        }
    }
}
//===============================================
void GAccountUi::onUsernameClear() {
    QLineEdit* lUsernameEdit = (QLineEdit*)getObj("account/username");
    lUsernameEdit->clear();
}
//===============================================
void GAccountUi::onUsernameClear(const QString& _text) {
    QPushButton* lUsernameClear = (QPushButton*)getObj("account/username/clear");
    bool lVisible = (_text != "");
    lUsernameClear->setVisible(lVisible);
}
//===============================================
void GAccountUi::onPasswordClear() {
    QLineEdit* lPasswordEdit = (QLineEdit*)getObj("account/password");
    lPasswordEdit->clear();
}
//===============================================
void GAccountUi::onPasswordClear(const QString& _text) {
    QPushButton* lPasswordClear = (QPushButton*)getObj("account/password/clear");
    bool lVisible = (_text != "");
    lPasswordClear->setVisible(lVisible);
}
//===============================================
void GAccountUi::onConfirmClear() {
    QLineEdit* lConfirmEdit = (QLineEdit*)getObj("account/confirm");
    lConfirmEdit->clear();
}
//===============================================
void GAccountUi::onConfirmClear(const QString& _text) {
    QPushButton* lConfirmClear = (QPushButton*)getObj("account/confirm/clear");
    bool lVisible = (_text != "");
    lConfirmClear->setVisible(lVisible);
}
//===============================================
