//===============================================
#include "GRequestUi.h"
#include "GPath.h"
#include "GXml.h"
#include "GPicto.h"
#include "GLog.h"
#include "GUser.h"
#include "GError.h"
#include "GCode.h"
#include "GSocket.h"
//===============================================
GRequestUi::GRequestUi(QWidget* _parent) :
GDialog(_parent) {
	createDoms();
	createLayout();
}
//===============================================
GRequestUi::~GRequestUi() {

}
//===============================================
void GRequestUi::createDoms() {
	m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("xml", "pad.xml"));
    m_dom->createXPath();
}
//===============================================
void GRequestUi::createLayout() {
    QHBoxLayout* lEmissionLayout = new QHBoxLayout;
    lEmissionLayout->setMargin(0);
    lEmissionLayout->setSpacing(10);

    QFrame* lEmissionTab = new QFrame;
    lEmissionTab->setLayout(lEmissionLayout);

    QHBoxLayout* lReceptionLayout = new QHBoxLayout;
    lReceptionLayout->setMargin(0);
    lReceptionLayout->setSpacing(10);

    QFrame* lReceptionTab = new QFrame;
    lReceptionTab->setLayout(lReceptionLayout);

    QTabWidget* lTabWidget = new QTabWidget;
    lTabWidget->setObjectName("flat");
    lTabWidget->addTab(lEmissionTab, "Emission");
    lTabWidget->addTab(lReceptionTab, "Reception");

    QVBoxLayout* lButtonLayout = new QVBoxLayout;
    lButtonLayout->setMargin(0);
    lButtonLayout->setSpacing(10);

    QHBoxLayout* lCenterLayout = new QHBoxLayout;
    lCenterLayout->addWidget(lTabWidget, 1);
    lCenterLayout->addLayout(lButtonLayout);
    lCenterLayout->setMargin(0);
    lCenterLayout->setSpacing(10);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lCenterLayout);
    lMainLayout->setMargin(10);
    lMainLayout->setSpacing(10);

    int lCount = countItem("request");
    QString lTitle = getItem("request", "title");
    QString lLogo = getItem("request", "logo");
    int lWidth = getItem("request", "width").toInt();
    int lHeight = getItem("request", "height").toInt();

    for(int i = 0; i < lCount; i++) {
        QString lCategory = getItem("request", "category", i);
        QString lType = getItem("request", "type", i);
        QString lStyle = getItem("request", "style", i);
        QString lAlign = getItem("request", "align", i);
        QString lAction = getItem("request", "action", i);
        QString lKey = getItem("request", "key", i);
        QString lKeyClear = getItem("request", "key_clear", i);
        QString lText = getItem("request", "text", i);
        QString lEchoMode = getItem("request", "echo_mode", i);
        QString lMask = getItem("request", "mask", i);
        bool lReadonly = (getItem("request", "readonly", i) == "1");
        QString lPicto = getItem("request", "picto", i);
        QString lPictoClear = getItem("request", "picto_clear", i);
        QString lPictoColor = getItem("request", "picto_color", i);
        int lPictoSize = getItem("request", "picto_size", i).toInt();

        QBoxLayout* lItemLayout = 0;

        if(lCategory == "emission") {
            lItemLayout = lEmissionLayout;
        }
        else if(lCategory == "reception") {
            lItemLayout = lReceptionLayout;
        }
        else if(lCategory == "button") {
            lItemLayout = lButtonLayout;
        }
        else {
            GERROR(eGERR, QString("Erreur la categorie n'existe pas.\n"
                    "- categorie : (%1)").arg(lCategory));
            GERROR_SHOWG(eGERR);
            continue;
        }

        GLOGT(eGOFF, QString("%1 : %2").arg(lCategory).arg(lType));

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
        else if(lType == "textedit") {
            QTextEdit* lTextEdit = new QTextEdit;
            lTextEdit->setObjectName(lStyle);
            lTextEdit->setLineWrapMode(QTextEdit::NoWrap);
            lTextEdit->setReadOnly(lReadonly);
            addObject(lTextEdit, lKey);
            lItemLayout->addWidget(lTextEdit);
        }
        else {
            GERROR(eGERR, QString("Erreur le type n'existe pas.\n"
                    "- type : (%1 : %2)").arg(lCategory).arg(lType));
            GERROR_SHOWG(eGERR);
            continue;
        }
    }

    setLayout(lMainLayout);
    setWindowTitle(lTitle);
    setWindowIcon(QIcon(GRES("img", lLogo)));
    resize(lWidth, lHeight);
}
//===============================================
void GRequestUi::onEvent() {
    QString lKey = m_objectMap[sender()];
    //===============================================
    // request/send
    //===============================================
    if(lKey == "request/send") {
        QTextEdit* lEmissionEdit = qobject_cast<QTextEdit*>(getObject("request/emission/textedit"));
        QTextEdit* lReceptionEdit = qobject_cast<QTextEdit*>(getObject("request/reception/textedit"));
        QString lEmissionText = lEmissionEdit->toPlainText();
        bool lXmlValid = true;
        bool lRequestValid = true;

        if(lEmissionText == "") {
            GERROR(eGERR, QString("L'editeur de texte est vide."));
        }
        else {
            GXml lXmlFormat;
            lXmlFormat.isValidXmlData(lEmissionText);
            lXmlValid &= !lXmlFormat.getErrors()->hasErrors();

            if(0 && !lXmlValid) {
                GERROR(eGERR, QString("Le format XML est invalide."));
            }
            else {
                GCode lRequestFormat(lEmissionText);
                QString lModule = lRequestFormat.getModule();
                QString lMethod = lRequestFormat.getMethod();

                GLOGT(eGOFF, lModule);
                GLOGT(eGOFF, lMethod);

                lRequestValid &= (lModule != "");
                lRequestValid &= (lMethod != "");

                if(0 && !lRequestValid) {
                    GERROR(eGERR, QString("Le format de la requete est invalide."));
                }
                else {
                    GSocket lClient;
                    QString lReceptionText = lClient.callServer(lEmissionText);
                    lReceptionEdit->setText(lReceptionText);
                    GLOGT(eGMSG, QString("[EMISSION] :\n%1").arg(lEmissionText));
                    GLOGT(eGMSG, QString("[RECEPTION] :\n%1").arg(lReceptionText));
                }
            }
        }
    }
    //===============================================
    // request/clear
    //===============================================
    else if(lKey == "request/clear") {
        QTextEdit* lTextEdit = qobject_cast<QTextEdit*>(getObject("request/textedit"));
        lTextEdit->clear();
    }
    //===============================================
    // else
    //===============================================
    else {
        GERROR(eGERR, QString("Erreur la cle n'existe pas.\n"
                "- cle : (%1)").arg(lKey));
    }
    //===============================================
    // end
    //===============================================
    GERROR_SHOWG(eGERR);
}
//===============================================
void GRequestUi::onEvent(const QString& _text) {

}
//===============================================