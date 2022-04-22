//===============================================
#include <GTableWidget.h>
#include "GSearchUi.h"
#include "GPath.h"
#include "GXml.h"
#include "GPicto.h"
#include "GLog.h"
#include "GUser.h"
#include "GError.h"
#include "GCode.h"
#include "GSocket.h"
//===============================================
GSearchUi::GSearchUi(QWidget* _parent) :
GDialog(_parent) {
    createDoms();
    createLayout();
}
//===============================================
GSearchUi::~GSearchUi() {

}
//===============================================
void GSearchUi::createDoms() {
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("xml", "pad.xml"));
    m_dom->createXPath();
}
//===============================================
void GSearchUi::createLayout() {
    QHBoxLayout* lListLayout = new QHBoxLayout;
    lListLayout->setMargin(0);
    lListLayout->setSpacing(10);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lListLayout);
    lMainLayout->setMargin(10);
    lMainLayout->setSpacing(10);

    int lCount = countItem("search");
    QString lTitle = getItem("search", "title");
    QString lLogo = getItem("search", "logo");
    int lWidth = getItem("search", "width").toInt();
    int lHeight = getItem("search", "height").toInt();

    for(int i = 0; i < lCount; i++) {
        QString lCategory = getItem("search", "category", i);
        QString lType = getItem("search", "type", i);
        QString lStyle = getItem("search", "style", i);
        QString lAlign = getItem("search", "align", i);
        QString lAction = getItem("search", "action", i);
        QString lKey = getItem("search", "key", i);
        QString lKeyClear = getItem("search", "key_clear", i);
        QString lText = getItem("search", "text", i);
        QString lEchoMode = getItem("search", "echo_mode", i);
        QString lMask = getItem("search", "mask", i);
        bool lReadonly = (getItem("search", "readonly", i) == "1");
        QString lPicto = getItem("search", "picto", i);
        QString lPictoClear = getItem("search", "picto_clear", i);
        QString lPictoColor = getItem("search", "picto_color", i);
        int lPictoSize = getItem("search", "picto_size", i).toInt();

        QBoxLayout* lItemLayout = 0;

        if(lCategory == "list") {
            lItemLayout = lListLayout;
        }
        else {
            GERROR(eGERR, QString(""
                    "Erreur la categorie n'existe pas.\n"
                    "categorie....: (%1)")
                    .arg(lCategory)
            );
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
        else if(lType == "tablewidget") {
            QTableWidget* lTableWidget = new QTableWidget;
            GTableWidget lTable(5, 3, lTableWidget);
            lTable.addData("Hello");
            lTable.addData("Hello");
            lTable.addData("Hello");
            lTable.addData("Hello");
            lTable.addData("Hello");
            lTable.addData("Hello");
            lItemLayout->addWidget(lTableWidget);
        }
        else {
            GERROR(eGERR, QString(""
                    "Erreur le type n'existe pas.\n"
                    "type.........: (%1 : %2)")
                    .arg(lCategory).arg(lType)
            );
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
void GSearchUi::onEvent() {
    QString lKey = m_objectMap[sender()];
    //===============================================
    // search/send
    //===============================================
    if(lKey == "search/send") {
        QTextEdit* lEmissionEdit = qobject_cast<QTextEdit*>(getObject("search/emission/textedit"));
        QTextEdit* lReceptionEdit = qobject_cast<QTextEdit*>(getObject("search/reception/textedit"));
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
        QTextEdit* lTextEdit = qobject_cast<QTextEdit*>(getObject("request/emission/textedit"));
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
void GSearchUi::onEvent(const QString& _text) {

}
//===============================================
