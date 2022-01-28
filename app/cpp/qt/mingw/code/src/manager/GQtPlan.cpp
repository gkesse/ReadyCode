//===============================================
#include "GQtPlan.h"
#include "GQtXml.h"
#include "GQtPicto.h"
#include "GQtLog.h"
#include "GQtScrollArea.h"
//===============================================
GQtPlan::GQtPlan(QWidget* _parent) :
GQtWidget(_parent) {
    GQTSTYLE(GQTRES("studio/css", "plan.css"));
    setObjectName("plan");
    createDoms();
    setLayout(createMainWindow());
    initSettings();
}
//===============================================
GQtPlan::~GQtPlan() {

}
//===============================================
void GQtPlan::createDoms() {
    m_dom.reset(new GQtXml);
    m_dom->loadXmlFile(GQTRES("studio/xml", "plan.xml"));
    m_dom->createXPath();
}
//===============================================
void GQtPlan::initSettings() {
    QString lTitle = getSettingItem("title");
    QString lLogo = getSettingItem("logo");
    int lWidth = getSettingItem("width").toInt();
    int lHeight = getSettingItem("height").toInt();
    bool lMaximizeOn = (getSettingItem("maximize_on") == "1");
    bool lFullscreenOn = (getSettingItem("fullscreen_on") == "1");

    setWindowTitle(lTitle);
    setWindowIcon(QIcon(GQTRES("studio/img", lLogo)));
    resize(lWidth, lHeight);
    if(lMaximizeOn) {
        showMaximized();
    }
    else if(lFullscreenOn) {
        showFullScreen();
    }
}
//===============================================
QString GQtPlan::getSettingItem(const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/settings']/%1").arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QLayout* GQtPlan::createMainWindow() {
    QVBoxLayout* lContentLayout = new QVBoxLayout;
    lContentLayout->setMargin(10);
    lContentLayout->setSpacing(10);

    int lCount = countMainWindowItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getMainWindowItem(i, "type");
        QString lText = getMainWindowItem(i, "text");
        QString lFontSize = getMainWindowItem(i, "font_size");
        QString lFontColor = getMainWindowItem(i, "font_color");

        if(lType == "titlebar") {
            lContentLayout->addWidget(createTitleBar());
        }
        else if(lType == "searchbar") {
            lContentLayout->addWidget(createSearchBar());
        }
        else if(lType == "message") {
            QLabel* lLabel = new QLabel;
            lLabel->setText(lText);
            lLabel->setAlignment(Qt::AlignCenter);
            QString lStyle = "";
            if(lFontSize != "") {
                lStyle += QString("QLabel {font-size: %1px;}").arg(lFontSize);
            }
            if(lFontColor != "") {
                lStyle += QString("QLabel {color: %1;}").arg(lFontColor);
            }
            lLabel->setStyleSheet(lStyle);

            GQtScrollArea* lLabelScroll = new GQtScrollArea;
            lLabelScroll->setWidget(lLabel);
            lLabelScroll->setWidgetResizable(true);
            lLabelScroll->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

            lContentLayout->addWidget(lLabelScroll);
        }
        else if(lType == "spacer") {
            lContentLayout->addStretch();
        }
    }

    QFrame* lContentPage = new QFrame;
    lContentPage->setLayout(lContentLayout);

    QScrollArea* lMainPage = new QScrollArea;
    lMainPage->setWidget(lContentPage);
    lMainPage->setWidgetResizable(true);
    lMainPage->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(lMainPage);
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(0);

    return lMainLayout;
}
//===============================================
int GQtPlan::countMainWindowItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/mainwindow']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getMainWindowItem(int _index, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/mainwindow']/map/data[position()=%1]/%2").arg(_index + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QWidget* GQtPlan::createTitleBar() {
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countTitleBarItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getTitleBarItem(i, "type");
        QString lName = getTitleBarItem(i, "name");
        QString lIcon = getTitleBarItem(i, "icon");
        QString lPicto = getTitleBarItem(i, "picto");
        QString lPictoColor = getTitleBarItem(i, "picto_color");

        if(lType == "button") {
            QPushButton* lButton = new QPushButton;
            lButton->setText(lName);
            lButton->setCursor(Qt::PointingHandCursor);
            if(lPicto != "") {
                if(lPictoColor == "") {
                    lPictoColor = "#ffffff";
                }
                lButton->setIcon(GQTPICTO(lPicto, lPictoColor));
            }
            lMainLayout->addWidget(lButton);
        }
        else if(lType == "spacer") {
            lMainLayout->addStretch();
        }
    }

    QFrame* lContentPage = new QFrame;
    lContentPage->setLayout(lMainLayout);

    GQtScrollArea* lMainPage = new GQtScrollArea;
    lMainPage->setWidget(lContentPage);
    lMainPage->setWidgetResizable(true);
    lMainPage->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    return lMainPage;
}
//===============================================
int GQtPlan::countTitleBarItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/titlebar']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getTitleBarItem(int _index, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/titlebar']/map/data[position()=%1]/%2").arg(_index + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QWidget* GQtPlan::createSearchBar() {
    QHBoxLayout* lOfferLayout = new QHBoxLayout;
    lOfferLayout->setMargin(0);
    lOfferLayout->setSpacing(10);

    QHBoxLayout* lLocationLayout = new QHBoxLayout;
    lLocationLayout->setMargin(0);
    lLocationLayout->setSpacing(10);

    QHBoxLayout* lFilterLayout = new QHBoxLayout;
    lFilterLayout->setMargin(0);
    lFilterLayout->setSpacing(10);

    QHBoxLayout* lDeliveryLayout = new QHBoxLayout;
    lDeliveryLayout->setMargin(0);
    lDeliveryLayout->setSpacing(10);

    QHBoxLayout* lSearchLayout = new QHBoxLayout;
    lSearchLayout->setMargin(0);
    lSearchLayout->setSpacing(10);
    lSearchLayout->setAlignment(Qt::AlignCenter);

    QBoxLayout* lItemLayout = 0;

    int lCount = countSearchBarItems();

    for(int i = 0; i < lCount; i++) {
        QString lCategory = getSearchBarItem(i, "category");
        QString lType = getSearchBarItem(i, "type");
        QString lName = getSearchBarItem(i, "name");
        QString lIcon = getSearchBarItem(i, "icon");
        QString lPicto = getSearchBarItem(i, "picto");
        QString lPictoColor = getSearchBarItem(i, "picto_color");
        int lPictoSize = getSearchBarItem(i, "picto_size").toInt();
        int lMinWidth = getSearchBarItem(i, "min_width").toInt();

        if(lCategory == "offer_layout") {
            lItemLayout = lOfferLayout;
        }
        else if(lCategory == "location_layout") {
            lItemLayout = lLocationLayout;
        }
        else if(lCategory == "filter_layout") {
            lItemLayout = lFilterLayout;
        }
        else if(lCategory == "delivery_layout") {
            lItemLayout = lDeliveryLayout;
        }
        else if(lCategory == "search_layout") {
            lItemLayout = lSearchLayout;
        }

        if(lItemLayout == 0) break;


        if(lType == "button") {
            QPushButton* lButton = new QPushButton;
            lButton->setText(lName);
            if(lPicto != "") {
                if(lPictoColor == "") lPictoColor = "#ffffff";
                lButton->setIcon(GQTPICTO(lPicto, lPictoColor));
            }
            lButton->setCursor(Qt::PointingHandCursor);
            lItemLayout->addWidget(lButton);
        }
        else if(lType == "button/icon") {
            QPushButton* lIcon;
            QPushButton* lButton = createButtonIcon(lName, &lIcon);
            if(lPicto != "") {
                if(lPictoColor == "") lPictoColor = "#ffffff";
                lIcon->setIcon(GQTPICTO(lPicto, lPictoColor));
            }
            lButton->setCursor(Qt::PointingHandCursor);
            lItemLayout->addWidget(lButton);
        }
        else if(lType == "button/icon/round") {
            QPushButton* lButton = new QPushButton;
            lButton->setObjectName("button_icon_round");
            if(lPicto != "") {
                if(lPictoColor == "") lPictoColor = "#ffffff";
                lButton->setIcon(GQTPICTO(lPicto, lPictoColor));
            }
            if(lPictoSize) {
                lButton->setIconSize(QSize(lPictoSize, lPictoSize));
            }
            lButton->setCursor(Qt::PointingHandCursor);
            lItemLayout->addWidget(lButton);
        }
        else if(lType == "radiobutton") {
            QRadioButton* lButton = new QRadioButton;
            lButton->setText(lName);
            lButton->setCursor(Qt::PointingHandCursor);
            lItemLayout->addWidget(lButton);
        }
        else if(lType == "checkbox") {
            QCheckBox* lCheckBox = new QCheckBox;
            lCheckBox->setText(lName);
            lCheckBox->setCursor(Qt::PointingHandCursor);
            lItemLayout->addWidget(lCheckBox);
        }
        else if(lType == "lineedit/icon") {
            QPushButton* lIcon;
            QLineEdit* lLineEdit = createLineEditIcon(&lIcon);
            lLineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
            lLineEdit->setPlaceholderText(lName);
            if(lMinWidth != 0) {
                lLineEdit->setMinimumWidth(lMinWidth);
            }
            if(lPicto != "") {
                if(lPictoColor == "") lPictoColor = "#ffffff";
                lIcon->setIcon(GQTPICTO(lPicto, lPictoColor));
            }
            lItemLayout->addWidget(lLineEdit);
        }
        else if(lType == "spacer") {
            lItemLayout->addStretch();
        }
    }

    QVBoxLayout* lContentLayout = new QVBoxLayout;
    lContentLayout->addLayout(lOfferLayout);
    lContentLayout->addLayout(lLocationLayout);
    lContentLayout->addLayout(lFilterLayout);
    lContentLayout->addLayout(lDeliveryLayout);
    lContentLayout->addLayout(lSearchLayout);
    lContentLayout->setMargin(20);
    lContentLayout->setSpacing(20);

    QFrame* lContentPage = new QFrame;
    lContentPage->setObjectName("plan_search");
    lContentPage->setLayout(lContentLayout);
    lContentPage->setMinimumSize(lContentPage->sizeHint());

    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->addWidget(lContentPage);
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    QFrame* lBodyPage = new QFrame;
    lBodyPage->setLayout(lMainLayout);

    GQtScrollArea* lMainPage = new GQtScrollArea;
    lMainPage->setWidget(lBodyPage);
    lMainPage->setWidgetResizable(true);
    lMainPage->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    return lMainPage;
}
//===============================================
int GQtPlan::countSearchBarItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/searchbar']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getSearchBarItem(int _index, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/searchbar']/map/data[position()=%1]/%2").arg(_index + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
