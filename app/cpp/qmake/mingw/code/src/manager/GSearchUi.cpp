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
    QHBoxLayout* lTableLayout = new QHBoxLayout;
    lTableLayout->setMargin(0);
    lTableLayout->setSpacing(10);

    QVBoxLayout* lButtonLayout = new QVBoxLayout;
    lButtonLayout->setMargin(0);
    lButtonLayout->setSpacing(10);

    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->addLayout(lTableLayout, 1);
    lMainLayout->addLayout(lButtonLayout);
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
        bool lReadonlyOn = (getItem("search", "readonly_on", i) == "1");
        bool lSelectRowOn = (getItem("search", "selectrow_on", i) == "1");
        bool lHorHeaderOn = (getItem("search", "hor_header_on", i) == "1");
        bool lVerHeaderOn = (getItem("search", "ver_header_on", i) == "1");
        bool lVerHeaderStretchLastOn = (getItem("search", "ver_header_stretch_last_on", i) == "1");
        bool lHorHeaderStretchLastOn = (getItem("search", "hor_header_stretch_last_on", i) == "1");
        QString lPicto = getItem("search", "picto", i);
        QString lPictoClear = getItem("search", "picto_clear", i);
        QString lPictoColor = getItem("search", "picto_color", i);
        int lPictoSize = getItem("search", "picto_size", i).toInt();

        QBoxLayout* lItemLayout = 0;

        if(lCategory == "table") {
            lItemLayout = lTableLayout;
        }
        else if(lCategory == "button") {
            lItemLayout = lButtonLayout;
        }
        else {
            GERROR(eGERR, QString(""
                    "Erreur la categorie n'existe pas.\n"
                    "categorie....: %1")
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
            lTableWidget->setObjectName(lStyle);

            if(lReadonlyOn) {
                lTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
            }
            if(lSelectRowOn) {
                lTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            }
            if(!lHorHeaderOn) {
                lTableWidget->horizontalHeader()->hide();
            }
            if(!lVerHeaderOn) {
                lTableWidget->verticalHeader()->hide();
            }
            if(lHorHeaderStretchLastOn) {
                lTableWidget->horizontalHeader()->setStretchLastSection(true);
            }
            if(lVerHeaderStretchLastOn) {
                lTableWidget->verticalHeader()->setStretchLastSection(true);
            }

            GTableWidget lTable(5, 3, lTableWidget);

            for(int i = 0; i < 3; i++) {
                lTable.addColHeader(QString("Col[%1]").arg(i));
            }

            for(int i = 0; i < 5; i++) {
                for(int j = 0; j < 3; j++) {
                    lTable.addData(QString("data[%1][%2]").arg(i).arg(j), i);
                }
            }
            connect(lTableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onClick(QTableWidgetItem*)));
            connect(lTableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(onDoubleClick(QTableWidgetItem*)));
            lItemLayout->addWidget(lTableWidget);
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
            GERROR(eGERR, QString("Erreur l'editeur de texte est vide."));
        }
        else {
            GXml lXmlFormat;
            lXmlFormat.isValidXmlData(lEmissionText);
            lXmlValid &= !lXmlFormat.getErrors()->hasErrors();

            if(0 && !lXmlValid) {
                GERROR(eGERR, QString("Erreur le format XML est invalide."));
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
                    GLOGT(eGMSG, QString("[EMISSION]...: %1\n%2").arg(lEmissionText.size()).arg(lEmissionText));
                    GLOGT(eGMSG, QString("[RECEPTION]..: %1\n%2").arg(lReceptionText.size()).arg(lReceptionText));
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
        GERROR(eGERR, QString(""
                "Erreur la cle n'existe pas.\n"
                "cle..........: %1")
                .arg(lKey)
        );
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
void GSearchUi::onClick(QTableWidgetItem* _item) {
    QString lData = _item->data(Qt::DisplayRole).toString();
    QString lKey = _item->data(Qt::UserRole).toString();
    GLOGT(eGOFF, QString(""
            "data.........: %1\n"
            "key..........: %2\n"
            "").arg(lData).arg(lKey)
    );
}
//===============================================
void GSearchUi::onDoubleClick(QTableWidgetItem* _item) {
    QString lData = _item->data(Qt::DisplayRole).toString();
    QString lKey = _item->data(Qt::UserRole).toString();
    GLOGT(eGOFF, QString(""
            "data.........: %1\n"
            "key..........: %2\n"
            "").arg(lData).arg(lKey)
    );
}
//===============================================
