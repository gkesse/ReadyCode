//===============================================
#include "GPadUi.h"
#include "GLoginUi.h"
#include "GRequestUi.h"
#include "GPath.h"
#include "GXml.h"
#include "GStyle.h"
#include "GPicto.h"
#include "GLog.h"
//===============================================
GPadUi::GPadUi(QWidget* _parent) :
GWidget(_parent) {
    GSTYLE(GRES("css", "style.css"));
    createDoms();
    createLayout();
}
//===============================================
GPadUi::~GPadUi() {

}
//===============================================
void GPadUi::createDoms() {
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("xml", "pad.xml"));
    m_dom->createXPath();
}
//===============================================
void GPadUi::createLayout() {
    QHBoxLayout* lHeaderLayout = new QHBoxLayout;
    lHeaderLayout->setMargin(0);
    lHeaderLayout->setSpacing(10);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lHeaderLayout);
    lMainLayout->setMargin(10);
    lMainLayout->setSpacing(10);

    int lCount = countItem("pad");
    QString lStyle = getItem("pad", "style");
    QString lTitle = getItem("pad", "title");
    QString lLogo = getItem("pad", "logo");
    int lWidth = getItem("pad", "width").toInt();
    int lHeight = getItem("pad", "height").toInt();

    for(int i = 0; i < lCount; i++) {
        QString lCategory = getItem("pad", "category", i);
        QString lType = getItem("pad", "type", i);
        QString lStyle = getItem("pad", "style", i);
        QString lAlign = getItem("pad", "align", i);
        QString lAction = getItem("pad", "action", i);
        QString lKey = getItem("pad", "key", i);
        QString lKeyClear = getItem("pad", "key_clear", i);
        QString lText = getItem("pad", "text", i);
        QString lEchoMode = getItem("pad", "echo_mode", i);
        QString lMask = getItem("pad", "mask", i);
        QString lPicto = getItem("pad", "picto", i);
        QString lPictoClear = getItem("pad", "picto_clear", i);
        QString lPictoColor = getItem("pad", "picto_color", i);
        int lPictoSize = getItem("pad", "picto_size", i).toInt();

        QBoxLayout* lItemLayout = 0;

        if(lCategory == "main") {
            lItemLayout = lMainLayout;
        }
        else if(lCategory == "header") {
            lItemLayout = lHeaderLayout;
        }
        else {
            GERROR(eGERR, QString(""
                    "Erreur la categorie n'existe pas.\n"
                    "categorie....: %1\n"
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
        else {
            GERROR(eGERR, QString(""
                    "Erreur le type n'existe pas.\n"
                    "type.........: %1 : %2\n"
                    "").arg(lCategory).arg(lType)
            );
            GERROR_SHOWG(eGERR);
            continue;
        }
    }

    setLayout(lMainLayout);
    setWindowTitle(lTitle);
    setWindowIcon(QIcon(GRES("img", lLogo)));
    resize(lWidth, lHeight);
    setObjectName(lStyle);

    addObject(new GLoginUi(this), "login/ui");
    addObject(new GRequestUi(this), "request/ui");
}
//===============================================
void GPadUi::onEvent() {
    QString lKey = m_objectMap[sender()];
    GLOGT(eGINF, lKey);
    //===============================================
    // header/connect
    //===============================================
    if(lKey == "header/connect") {
        QDialog* lLoginUi = qobject_cast<GLoginUi*>(getObject("login/ui"));
        lLoginUi->exec();
    }
    //===============================================
    // header/request
    //===============================================
    else if(lKey == "header/request") {
        QDialog* lRequestUi = qobject_cast<GRequestUi*>(getObject("request/ui"));
        lRequestUi->exec();
    }
    //===============================================
    // else
    //===============================================
    else {
        GERROR(eGERR, QString("Erreur la cle n'existe pas.\n"
                "- cle : %1").arg(lKey));
    }
    //===============================================
    // end
    //===============================================
    GERROR_SHOWG(eGERR);
}
//===============================================
void GPadUi::onEvent(const QString& _text) {

}
//===============================================
bool GPadUi::eventFilter(QObject* _obj, QEvent* _event) {
    return QObject::eventFilter(_obj, _event);
}
//===============================================
