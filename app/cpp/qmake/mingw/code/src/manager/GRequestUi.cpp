//===============================================
#include "GRequestUi.h"
#include "GLoginUi.h"
#include "GSearchUi.h"
#include "GPath.h"
#include "GXml.h"
#include "GPicto.h"
#include "GLog.h"
#include "GUser.h"
#include "GError.h"
#include "GCode.h"
#include "GSocket.h"
#include "GRequest.h"
#include "GTableWidget.h"
//===============================================
GRequestUi::GRequestUi(QWidget* _parent) :
GDialog(_parent) {
    m_dataOffset = 0;
    m_dataSize = 2;
    createDoms();
    createLayout();
}
//===============================================
GRequestUi::~GRequestUi() {

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
    QString lStyle = getItem("request", "style");

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
        bool lReadonly = (getItem("request", "readonly_on", i) == "1");
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
            GERROR(eGERR, QString(""
                    "Erreur la categorie n'existe pas.\n"
                    "categorie....: (%1)\n")
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
        else if(lType == "textedit") {
            QTextEdit* lTextEdit = new QTextEdit;
            addObj(lKey, lTextEdit);
            lTextEdit->setObjectName(lStyle);
            lTextEdit->setLineWrapMode(QTextEdit::NoWrap);
            lTextEdit->setReadOnly(lReadonly);
            lItemLayout->addWidget(lTextEdit);
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
    setWindowTitle(lTitle);
    setWindowIcon(QIcon(GRES("img", lLogo)));
    resize(lWidth, lHeight);
    setObjectName(lStyle);

    addObj("login/ui", (void*)(new GLoginUi(this)));
    addObj("search/ui", (void*)(new GSearchUi(this)));
}
//===============================================
void GRequestUi::onEvent() {
    QString lKey = getKey(sender());

    if(lKey == "request/send") {
        onRequestSend();
    }
    else if(lKey == "request/clear") {
        onRequestClear();
    }
    else if(lKey == "request/search") {
        onRequestSearch();
    }
    else {
        onErrorKey(lKey);
    }

    GERROR_SHOWG(eGERR);
}
//===============================================
void GRequestUi::onEvent(const QString& _text) {
    QString lKey = getKey(sender());

    if(lKey == "search/ui") {
        if(_text == "search/next") {
            onRequestSearchNext();
        }
        else if(_text == "search/previous") {
            onRequestSearchPrevious();
        }
        else {
            onErrorKey(_text);
        }
    }
    else {
        onErrorKey(lKey);
    }

    GERROR_SHOWG(eGERR);
}
//===============================================
void GRequestUi::onRequestSend() {
    QTextEdit* lEmissionEdit = (QTextEdit*)getObj("request/emission/textedit");
    QTextEdit* lReceptionEdit = (QTextEdit*)getObj("request/reception/textedit");
    QString lEmissionText = lEmissionEdit->toPlainText();
    bool lXmlValid = true;
    bool lRequestValid = true;

    if(lEmissionText == "") {
        GERROR(eGERR, QString("Erreur l'editeur de texte est vide."));
    }
    else {
        GXml lXmlFormat;
        lXmlFormat.isValidXmlData(lEmissionText);
        lXmlValid &= !lXmlFormat.hasErrors();

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
                GERROR(eGERR, QString("Erreur le format de la requete est invalide."));
            }
            else {
                GSocket lClient;
                QString lReceptionText = lClient.callServer(lEmissionText);
                lReceptionEdit->setText(lReceptionText);
                GLOGT(eGMSG, QString("[EMISSION]...: (%1)\n(%2)\n").arg(lEmissionText.size()).arg(lEmissionText));
                GLOGT(eGMSG, QString("[RECEPTION]..: (%1)\n(%2)\n").arg(lReceptionText.size()).arg(lReceptionText));
            }
        }
    }
}
//===============================================
void GRequestUi::onRequestClear() {
    QTextEdit* lTextEdit = (QTextEdit*)getObj("request/emission/textedit");
    lTextEdit->clear();
}
//===============================================
void GRequestUi::onRequestSearch() {
    GSearchUi* lSearchUi = (GSearchUi*)getObj("search/ui");
    getRequestList();
    int lOk = lSearchUi->exec();

    if(lOk == QDialog::Accepted) {
        int lIndex = lSearchUi->getCurrentIndex();
        if(lIndex >= 0) {
            GRequest* lReq = m_reqs->getReqs().at(lIndex);
            QString lMsg = lReq->getMsg();
            QTextEdit* lEmissionEdit = (QTextEdit*)getObj("request/emission/textedit");
            lEmissionEdit->setText(lMsg);
        }
    }
}
//===============================================
void GRequestUi::onRequestSearchNext() {
    getRequestList(m_dataOffset + m_dataSize);
}
//===============================================
void GRequestUi::onRequestSearchPrevious() {
    getRequestList(m_dataOffset - m_dataSize);
}
//===============================================
void GRequestUi::getRequestList(int _newOffset) {
    if(_newOffset < 0) return;
    if(_newOffset >= m_dataSize) return;
    if(m_dataSize == 0) return;
    m_dataOffset = _newOffset;
    m_reqs.reset(new GRequest);
    m_reqs->setDataOffset(m_dataOffset);
    m_reqs->setDataSize(m_dataSize);
    m_reqs->getRequestList();
    GSearchUi* lSearchUi = (GSearchUi*)getObj("search/ui");
    QTableWidget* lTableWidget = (QTableWidget*)lSearchUi->getObj("search/tablewidget");
    int lRows = m_reqs->getReqs().size();
    int lCols = m_reqs->getHeaders().size();
    GTableWidget lTable(lRows, lCols, lTableWidget);

    for(int i = 0; i < lCols; i++) {
        QString lHeader = m_reqs->getHeaders().at(i);
        lTable.addColHeader(lHeader);
    }

    for(int i = 0; i < lRows; i++) {
        GRequest* lReq = m_reqs->getReqs().at(i);
        lTable.addData(lReq->getId(), i);
        lTable.addData(lReq->getModule(), i);
        lTable.addData(lReq->getMethod(), i);
        lTable.addData(lReq->getMsg(), i);
    }

    lSearchUi->initOptions();
}
//===============================================
