//===============================================
#include "GCvUi.h"
#include "GTitleBarMdi.h"
#include "GPath.h"
#include "GXml.h"
#include "GPicto.h"
#include "GLog.h"
#include "GUser.h"
//===============================================
GCvUi::GCvUi(QWidget* _parent)
: GWidget(_parent) {
    createDoms();
    createLayout();
}
//===============================================
GCvUi::~GCvUi() {

}
//===============================================
void GCvUi::createLayout() {
    QWidget* lParent = parentWidget();
    lParent->setWindowTitle("titre");

    GTitleBarMdi* lTitleBar = new GTitleBarMdi(lParent);

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

    QVBoxLayout* lBodyLayout = new QVBoxLayout;
    lBodyLayout->addLayout(lUsernameLayout);
    lBodyLayout->addLayout(lPasswordLayout);
    lBodyLayout->addLayout(lMessageLayout);
    lBodyLayout->addLayout(lButtonLayout);
    lBodyLayout->addLayout(lAccountLayout);
    lBodyLayout->setMargin(10);
    lBodyLayout->setSpacing(10);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(lTitleBar);
    lMainLayout->addLayout(lBodyLayout);
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(0);

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
            GERROR(eGERR, QString(""
                    "Erreur la categorie (%1) n'existe pas.\n"
                    "").arg(lCategory)
            );
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
        else if(lType == "label/message") {
            QLabel* lLabel = new QLabel;
            addObj(lKey, lLabel);
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
            GERROR(eGERR, QString(""
                    "Erreur le type (%1 : %2) n'existe pas.\n"
                    "").arg(lCategory).arg(lType)
            );
            GERROR_SHOWG(eGERR);
            continue;
        }
    }

    setLayout(lMainLayout);
    resize(lWidth, lHeight);
    setObjectName(lStyle);

    setMinimumWidth(lWidth);

    if(lWidthFix) {
        setFixedWidth(lWidth);
    }
    if(lHeightFix) {
        setFixedHeight(sizeHint().height());
    }
}
//===============================================
void GCvUi::onEvent() {
    QString lKey = getKey(sender());
    //===============================================
    // actions
    //===============================================
    if(lKey == "login/connect") {
        onConnect();
    }
    //===============================================
    else if(lKey == "login/username/clear") {
        onUsernameClear();
    }
    //===============================================
    else if(lKey == "login/password/clear") {
        onPasswordClear();
    }
    //===============================================
    // else
    //===============================================
    else {
        onErrorKey(lKey);
    }
    //===============================================
    // end
    //===============================================
    GERROR_SHOWG(eGERR);
}
//===============================================
void GCvUi::onEvent(const QString& _text) {
    QString lKey = getKey(sender());
    //===============================================
    // actions
    //===============================================
    if(lKey == "login/username") {
        onUsernameClear(_text);
    }
    //===============================================
    else if(lKey == "login/password") {
        onPasswordClear(_text);
    }
    //===============================================
    // else
    //===============================================
    else {
        onErrorKey(lKey);
    }
    //===============================================
    // end
    //===============================================
    GERROR_SHOWG(eGERR);
}
//===============================================
void GCvUi::onConnect() {
    QLineEdit* lUsernameEdit = (QLineEdit*)getObj("login/username");
    QLineEdit* lPasswordEdit = (QLineEdit*)getObj("login/password");
    QLabel* lErrorLabel = (QLabel*)getObj("login/error");

    QString lUsername = lUsernameEdit->text();
    QString lPassword = lPasswordEdit->text();

    if(!lErrorLabel->isHidden()) {
        lErrorLabel->hide();
        setFixedHeight(sizeHint().height());
    }

    if(lUsername == "") {
        lErrorLabel->setText("Le nom d'utilisateur est obligatoire.");
        lErrorLabel->show();
        setFixedHeight(sizeHint().height());
    }
    else if(lPassword == "") {
        lErrorLabel->setText("Le mot de passe est obligatoire.");
        lErrorLabel->show();
        setFixedHeight(sizeHint().height());
    }
    else {
        bool lUsernameOn = GUser().hasUser(lUsername);
        bool lPasswordOn = GUser().hasUser(lUsername, lPassword);

        if(!lUsernameOn) {
            lErrorLabel->setText("Le nom d'utilisateur n'existe pas.");
            lErrorLabel->show();
            setFixedHeight(sizeHint().height());
        }
        else if(!lPasswordOn) {
            lErrorLabel->setText("Le mot de passe est incorrect.");
            lErrorLabel->show();
            setFixedHeight(sizeHint().height());
        }
    }
}
//===============================================
void GCvUi::onUsernameClear() {
    QLineEdit* lUsernameEdit = (QLineEdit*)getObj("login/username");
    lUsernameEdit->clear();
}
//===============================================
void GCvUi::onUsernameClear(const QString& _text) {
    QPushButton* lUsernameClear = (QPushButton*)getObj("login/username/clear");
    bool lVisible = (_text != "");
    lUsernameClear->setVisible(lVisible);
}
//===============================================
void GCvUi::onPasswordClear() {
    QLineEdit* lPasswordEdit = (QLineEdit*)getObj("login/password");
    lPasswordEdit->clear();
}
//===============================================
void GCvUi::onPasswordClear(const QString& _text) {
    QPushButton* lPasswordClear = (QPushButton*)getObj("login/password/clear");
    bool lVisible = (_text != "");
    lPasswordClear->setVisible(lVisible);
}
//===============================================
