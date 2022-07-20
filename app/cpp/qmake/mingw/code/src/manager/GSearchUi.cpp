//===============================================
#include <GTableWidget.h>
#include "GSearchUi.h"
#include "GPath.h"
#include "GXml.h"
#include "GPicto.h"
#include "GLog.h"
#include "GUser.h"
#include "GCode.h"
#include "GSocket.h"
//===============================================
GSearchUi::GSearchUi(QWidget* _parent) :
GDialog(_parent) {
    m_readonlyOn = false;
    m_selectRowOn = false;
    m_horHeaderOn = true;
    m_verHeaderOn = false;
    m_horHeaderStretchLastOn = false;
    m_verHeaderStretchLastOn = false;
    m_currentItem = 0;
    m_currentIndex = -1;
    //
    createDoms();
    createLayout();
    //
    connect(this, SIGNAL(onEmit(QString)), _parent, SLOT(onEvent(QString)));
}
//===============================================
GSearchUi::~GSearchUi() {

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
    QString lStyle = getItem("search", "style");

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
        bool lColumnToContentOn = (getItem("search", "column_to_content_on", i) == "1");
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
        else if(lType == "tablewidget") {
            QTableWidget* lTableWidget = new QTableWidget;
            addObj(lKey, lTableWidget);
            lTableWidget->setObjectName(lStyle);
            //
            setReadonlyOn(lReadonlyOn);
            setSelectRowOn(lSelectRowOn);
            setHorHeaderOn(lHorHeaderOn);
            setVerHeaderOn(lVerHeaderOn);
            setHorHeaderStretchLastOn(lHorHeaderStretchLastOn);
            setVerHeaderStretchLastOn(lVerHeaderStretchLastOn);
            setColumnToContentOn(lColumnToContentOn);
            //
            connect(lTableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onClick(QTableWidgetItem*)));
            connect(lTableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(onDoubleClick(QTableWidgetItem*)));
            lItemLayout->addWidget(lTableWidget);
        }
        else {
            GERROR(eGERR, QString(""
                    "Erreur le type n'existe pas.\n"
                    "type.........: %1 : (%2)\n"
                    "").arg(lCategory).arg(lType)
            );
            GERROR_SHOWG(eGERR);
            continue;
        }
    }

    setLayout(lMainLayout);
    setObjectName(lStyle);
    setWindowTitle(lTitle);
    setWindowIcon(QIcon(GRES("img", lLogo)));
    resize(lWidth, lHeight);
}
//===============================================
void GSearchUi::setReadonlyOn(bool _isReadonlyOn) {
    m_readonlyOn = _isReadonlyOn;
}
//===============================================
void GSearchUi::setSelectRowOn(bool _isSelectRowOn) {
    m_selectRowOn = _isSelectRowOn;
}
//===============================================
void GSearchUi::setHorHeaderOn(bool _isHorHeaderOn) {
    m_horHeaderOn = _isHorHeaderOn;
}
//===============================================
void GSearchUi::setVerHeaderOn(bool _isVerHeaderOn) {
    m_verHeaderOn = _isVerHeaderOn;
}
//===============================================
void GSearchUi::setHorHeaderStretchLastOn(bool _isHorHeaderStretchLastOn) {
    m_horHeaderStretchLastOn = _isHorHeaderStretchLastOn;
}
//===============================================
void GSearchUi::setVerHeaderStretchLastOn(bool _isVerHeaderStretchLastOn) {
    m_verHeaderStretchLastOn = _isVerHeaderStretchLastOn;
}
//===============================================
void GSearchUi::setColumnToContentOn(bool _isColumnToContentOn) {
    m_columnToContentOn = _isColumnToContentOn;
}
//===============================================
void GSearchUi::initOptions() {
    QTableWidget* lTableWidget = (QTableWidget*)getObj("search/tablewidget");

    if(m_readonlyOn) {
        lTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
    if(m_selectRowOn) {
        lTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    }
    if(!m_horHeaderOn) {
        lTableWidget->horizontalHeader()->hide();
    }
    if(!m_verHeaderOn) {
        lTableWidget->verticalHeader()->hide();
    }
    if(m_horHeaderStretchLastOn) {
        lTableWidget->horizontalHeader()->setStretchLastSection(true);
    }
    if(m_verHeaderStretchLastOn) {
        lTableWidget->verticalHeader()->setStretchLastSection(true);
    }
    if(m_columnToContentOn) {
        lTableWidget->resizeColumnsToContents();
    }
    clearIndex();
}
//===============================================
int GSearchUi::getCurrentIndex() const {
    return m_currentIndex;
}
//===============================================
void GSearchUi::clearIndex() {
    m_currentItem = 0;
    m_currentIndex = 0;
}
//===============================================
void GSearchUi::onEvent() {
    QString lKey = getKey(sender());
    //===============================================
    // search/select
    //===============================================
    if(lKey == "search/select") {
        if(m_currentItem != 0) {
            m_currentIndex = m_currentItem->data(Qt::UserRole).toInt();
            accept();
        }
        else {
            GERROR(eGERR, QString("Erreur aucune donnee n'a ete selectionne.\n"));
        }
    }
    //===============================================
    // search/next
    //===============================================
    else if(lKey == "search/next") {
        emit onEmit(lKey);
    }
    //===============================================
    // search/previous
    //===============================================
    else if(lKey == "search/previous") {
        emit onEmit(lKey);
    }
    //===============================================
    // else
    //===============================================
    else {
        GERROR(eGERR, QString(""
                "Erreur la cle n'existe pas.\n"
                "cle..........: (%1)\n")
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
            "data.........: (%1)\n"
            "key..........: (%2)\n"
            "").arg(lData).arg(lKey)
    );
    m_currentItem = _item;
}
//===============================================
void GSearchUi::onDoubleClick(QTableWidgetItem* _item) {
    QString lData = _item->data(Qt::DisplayRole).toString();
    m_currentIndex = _item->data(Qt::UserRole).toInt();
    GLOGT(eGOFF, QString(""
            "data.........: (%1)\n"
            "key..........: (%2)\n"
            "").arg(lData).arg(m_currentIndex)
    );
    accept();
}
//===============================================
