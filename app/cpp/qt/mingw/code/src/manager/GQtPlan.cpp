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

        if(lType == "message") {
            lContentLayout->addWidget(createMainWindow(i));
        }
        else if(lType == "titlebar") {
            lContentLayout->addWidget(createTitleBar());
        }
        else if(lType == "searchbar") {
            lContentLayout->addWidget(createSearchBar());
        }
        else if(lType == "quick_access") {
            lContentLayout->addWidget(createQuickAccess());
        }
        else if(lType == "recent_search") {
            lContentLayout->addWidget(createRecentSearch());
        }
        else if(lType == "top_category") {
            lContentLayout->addWidget(createTopCategory());
        }
        else if(lType == "holiday") {
            lContentLayout->addWidget(createHoliday());
        }
        else if(lType == "location_map") {
            lContentLayout->addWidget(createLocationMap());
        }
        else if(lType == "community") {
            lContentLayout->addWidget(createCommunity());
        }
        else if(lType == "motivation") {
            lContentLayout->addWidget(createMotivation());
        }
        else if(lType == "quick_link") {
            lContentLayout->addWidget(createQuickLink());
        }
        else if(lType == "about") {
            lContentLayout->addWidget(createAbout());
        }
        else if(lType == "partner") {
            lContentLayout->addWidget(createPartner());
        }
        else if(lType == "social_networks") {
            lContentLayout->addWidget(createSocialNetworks());
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
QWidget* GQtPlan::createMainWindow(int _index) {
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countMainWindowItems(_index);

    for(int i = 0; i < lCount; i++) {
        QString lType = getMainWindowItem(_index, i, "type");
        QString lText = getMainWindowItem(_index, i, "text");
        QString lName = getMainWindowItem(_index, i, "name");
        QString lFontSize = getMainWindowItem(_index, i, "font_size");
        QString lFontColor = getMainWindowItem(_index, i, "font_color");
        QString lPicto = getMainWindowItem(_index, i, "picto");
        QString lPictoColor = getMainWindowItem(_index, i, "picto_color");
        int lPictoSize = getMainWindowItem(_index, i, "picto_size").toInt();

        if(lType == "label") {
            QLabel* lLabel = new QLabel;
            lLabel->setText(lText);
            QString lStyle = "";
            if(lFontSize != "") {
                lStyle += QString("QLabel {font-size: %1px;}").arg(lFontSize);
            }
            if(lFontColor != "") {
                lStyle += QString("QLabel {color: %1;}").arg(lFontColor);
            }
            lLabel->setStyleSheet(lStyle);

            lMainLayout->addWidget(lLabel);
        }
        else if(lType == "button") {
            QPushButton* lButton = new QPushButton;
            lButton->setObjectName("plan_button_title");
            lButton->setText(lName);
            if(lPicto != "") {
                if(lPictoColor == "") lPictoColor = "#ffffff";
                lButton->setIcon(GQTPICTO(lPicto, lPictoColor));
            }
            if(lPictoSize) {
                lButton->setIconSize(QSize(lPictoSize, lPictoSize));
            }
            QString lStyle = "";
            if(lFontSize != "") {
                lStyle += QString("QPushButton {font-size: %1px;}").arg(lFontSize);
            }
            if(lFontColor != "") {
                lStyle += QString("QPushButton {color: %1;}").arg(lFontColor);
            }
            lButton->setStyleSheet(lStyle);
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
int GQtPlan::countMainWindowItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/mainwindow']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
int GQtPlan::countMainWindowItems(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/mainwindow']/map/data[position()=%1]/map/data").arg(_index + 1));
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
QString GQtPlan::getMainWindowItem(int _i, int _j, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/mainwindow']/map/data[position()=%1]/map/data[position()=%2]/%3").arg(_i+ 1).arg(_j+ 1).arg(_data));
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
QWidget* GQtPlan::createQuickAccess() {
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countQuickAccessItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getQuickAccessItem(i, "type");
        QString lName = getQuickAccessItem(i, "name");
        QString lPicto = getQuickAccessItem(i, "picto");
        QString lPictoColor = getQuickAccessItem(i, "picto_color");

        if(lType == "button/icon") {
            QPushButton* lIcon;
            QPushButton* lButton = createButtonIcon(lName, &lIcon);
            if(lPicto != "") {
                if(lPictoColor == "") lPictoColor = "#ffffff";
                lIcon->setIcon(GQTPICTO(lPicto, lPictoColor));
            }
            lButton->setCursor(Qt::PointingHandCursor);
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
int GQtPlan::countQuickAccessItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/quick_access']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getQuickAccessItem(int _index, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/quick_access']/map/data[position()=%1]/%2").arg(_index + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QWidget* GQtPlan::createRecentSearch() {
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countRecentSearchItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getRecentSearchItem(i, "type");

        if(lType == "box") {
            lMainLayout->addWidget(createRecentSearch(i));
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
QWidget* GQtPlan::createRecentSearch(int _index) {
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->setMargin(10);
    lMainLayout->setSpacing(10);

    QHBoxLayout* lTitleLayout = 0;
    QHBoxLayout* lCategoryLayout = 0;
    QHBoxLayout* lLocationLayout = 0;
    QBoxLayout* lItemLayout = 0;

    int lCount = countSearchBarItems();

    int lMinWidth = getRecentSearchItem(_index, "min_width").toInt();

    for(int i = 0; i < lCount; i++) {
        QString lCategory = getRecentSearchItem(_index, i, "category");
        QString lType = getRecentSearchItem(_index, i, "type");
        QString lText = getRecentSearchItem(_index, i, "text");
        QString lName = getRecentSearchItem(_index, i, "name");
        QString lFontColor = getRecentSearchItem(_index, i, "font_color");
        QString lFontSize = getRecentSearchItem(_index, i, "font_size");
        QString lPicto = getRecentSearchItem(_index, i, "picto");
        QString lPictoColor = getRecentSearchItem(_index, i, "picto_color");
        int lPictoSize = getRecentSearchItem(_index, i, "picto_size").toInt();

        if(lCategory == "main_layout") {
            lItemLayout = lMainLayout;
        }
        else if(lCategory == "title_layout") {
            if(!lTitleLayout) {
                lTitleLayout = new QHBoxLayout;
                lTitleLayout->setMargin(0);
                lTitleLayout->setSpacing(10);
                lMainLayout->addLayout(lTitleLayout);
            }
            lItemLayout = lTitleLayout;
        }
        else if(lCategory == "category_layout") {
            if(!lCategoryLayout) {
                lCategoryLayout = new QHBoxLayout;
                lCategoryLayout->setMargin(0);
                lCategoryLayout->setSpacing(10);
                lMainLayout->addLayout(lCategoryLayout);
            }
            lItemLayout = lCategoryLayout;
        }
        else if(lCategory == "location_layout") {
            if(!lLocationLayout) {
                lLocationLayout = new QHBoxLayout;
                lLocationLayout->setMargin(0);
                lLocationLayout->setSpacing(10);
                lMainLayout->addLayout(lLocationLayout);
            }
            lItemLayout = lLocationLayout;
        }

        if(lItemLayout == 0) break;

        if(lType == "label") {
            QLabel* lLabel = new QLabel;
            lLabel->setText(lText);
            QString lStyle = "";
            if(lFontSize != "") {
                lStyle += QString("QLabel {font-size: %1px;}").arg(lFontSize);
            }
            if(lFontColor != "") {
                lStyle += QString("QLabel {color: %1;}").arg(lFontColor);
            }
            lLabel->setStyleSheet(lStyle);

            lItemLayout->addWidget(lLabel);
        }
        else if(lType == "button") {
            QPushButton* lButton = new QPushButton;
            lButton->setObjectName("plan_button_title");
            lButton->setText(lName);
            if(lPicto != "") {
                if(lPictoColor == "") lPictoColor = "#ffffff";
                lButton->setIcon(GQTPICTO(lPicto, lPictoColor));
            }
            if(lPictoSize != 0) {
                lButton->setIconSize(QSize(lPictoSize, lPictoSize));
            }
            lButton->setCursor(Qt::PointingHandCursor);
            lItemLayout->addWidget(lButton);
        }
        else if(lType == "spacer") {
            lItemLayout->addStretch();
        }
    }

    QFrame* lBodyPage = new QFrame;
    lBodyPage->setLayout(lMainLayout);

    GQtScrollArea* lMainPage = new GQtScrollArea;
    lMainPage->setWidget(lBodyPage);
    lMainPage->setWidgetResizable(true);
    lMainPage->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    QVBoxLayout* lFormLayout = new QVBoxLayout;
    lFormLayout->addWidget(lMainPage);
    lFormLayout->setMargin(0);
    lFormLayout->setSpacing(0);

    QFrame* lFormPage = new QFrame;
    lFormPage->setObjectName("plan_box");
    lFormPage->setLayout(lFormLayout);

    return lFormPage;
}
//===============================================
int GQtPlan::countRecentSearchItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/recent_search']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
int GQtPlan::countRecentSearchItems(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/recent_search']/map/data[position()=%1]/map/data").arg(_index + 1));
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getRecentSearchItem(int _index, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/recent_search']/map/data[position()=%1]/%2").arg(_index + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtPlan::getRecentSearchItem(int _i, int _j, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/recent_search']/map/data[position()=%1]/map/data[position()=%2]/%3").arg(_i + 1).arg(_j + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QWidget* GQtPlan::createTopCategory() {
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countRecentSearchItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getRecentSearchItem(i, "type");

        if(lType == "box") {
            lMainLayout->addWidget(createRecentSearch(i));
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
int GQtPlan::countTopCategoryItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/top_category']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getTopCategoryItem(int _index, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/top_category']/map/data[position()=%1]/%2").arg(_index + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QWidget* GQtPlan::createHoliday() {
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countRecentSearchItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getRecentSearchItem(i, "type");

        if(lType == "box") {
            lMainLayout->addWidget(createRecentSearch(i));
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
int GQtPlan::countHolidayItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/holiday']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getHolidayItem(int _index, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/holiday']/map/data[position()=%1]/%2").arg(_index + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QWidget* GQtPlan::createLocationMap() {
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countRecentSearchItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getRecentSearchItem(i, "type");

        if(lType == "box") {
            lMainLayout->addWidget(createRecentSearch(i));
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
int GQtPlan::countLocationMapItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/location_map']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getLocationMapItem(int _index, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/location_map']/map/data[position()=%1]/%2").arg(_index + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QWidget* GQtPlan::createCommunity() {
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countRecentSearchItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getRecentSearchItem(i, "type");

        if(lType == "box") {
            lMainLayout->addWidget(createRecentSearch(i));
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
int GQtPlan::countCommunityItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/community']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getCommunityItem(int _index, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/community']/map/data[position()=%1]/%2").arg(_index + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QWidget* GQtPlan::createMotivation() {
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countQuickAccessItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getQuickAccessItem(i, "type");
        QString lName = getQuickAccessItem(i, "name");
        QString lPicto = getQuickAccessItem(i, "picto");
        QString lPictoColor = getQuickAccessItem(i, "picto_color");

        if(lType == "button/icon") {
            QPushButton* lIcon;
            QPushButton* lButton = createButtonIcon(lName, &lIcon);
            if(lPicto != "") {
                if(lPictoColor == "") lPictoColor = "#ffffff";
                lIcon->setIcon(GQTPICTO(lPicto, lPictoColor));
            }
            lButton->setCursor(Qt::PointingHandCursor);
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
int GQtPlan::countMotivationItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/motivation']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getMotivationItem(int _index, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/motivation']/map/data[position()=%1]/%2").arg(_index + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QWidget* GQtPlan::createQuickLink() {
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countQuickAccessItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getQuickAccessItem(i, "type");
        QString lName = getQuickAccessItem(i, "name");
        QString lPicto = getQuickAccessItem(i, "picto");
        QString lPictoColor = getQuickAccessItem(i, "picto_color");

        if(lType == "button/icon") {
            QPushButton* lIcon;
            QPushButton* lButton = createButtonIcon(lName, &lIcon);
            if(lPicto != "") {
                if(lPictoColor == "") lPictoColor = "#ffffff";
                lIcon->setIcon(GQTPICTO(lPicto, lPictoColor));
            }
            lButton->setCursor(Qt::PointingHandCursor);
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
int GQtPlan::countQuickLinkItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/quick_link']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getQuickLinkItem(int _index, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/quick_link']/map/data[position()=%1]/%2").arg(_index + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QWidget* GQtPlan::createAbout() {
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countQuickAccessItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getQuickAccessItem(i, "type");
        QString lName = getQuickAccessItem(i, "name");
        QString lPicto = getQuickAccessItem(i, "picto");
        QString lPictoColor = getQuickAccessItem(i, "picto_color");

        if(lType == "button/icon") {
            QPushButton* lIcon;
            QPushButton* lButton = createButtonIcon(lName, &lIcon);
            if(lPicto != "") {
                if(lPictoColor == "") lPictoColor = "#ffffff";
                lIcon->setIcon(GQTPICTO(lPicto, lPictoColor));
            }
            lButton->setCursor(Qt::PointingHandCursor);
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
int GQtPlan::countAboutItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/about']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getAboutItem(int _index, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/about']/map/data[position()=%1]/%2").arg(_index + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QWidget* GQtPlan::createPartner() {
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countQuickAccessItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getQuickAccessItem(i, "type");
        QString lName = getQuickAccessItem(i, "name");
        QString lPicto = getQuickAccessItem(i, "picto");
        QString lPictoColor = getQuickAccessItem(i, "picto_color");

        if(lType == "button/icon") {
            QPushButton* lIcon;
            QPushButton* lButton = createButtonIcon(lName, &lIcon);
            if(lPicto != "") {
                if(lPictoColor == "") lPictoColor = "#ffffff";
                lIcon->setIcon(GQTPICTO(lPicto, lPictoColor));
            }
            lButton->setCursor(Qt::PointingHandCursor);
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
int GQtPlan::countPartnerItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/partner']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getPartnerItem(int _index, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/partner']/map/data[position()=%1]/%2").arg(_index + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QWidget* GQtPlan::createSocialNetworks() {
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countQuickAccessItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getQuickAccessItem(i, "type");
        QString lName = getQuickAccessItem(i, "name");
        QString lPicto = getQuickAccessItem(i, "picto");
        QString lPictoColor = getQuickAccessItem(i, "picto_color");

        if(lType == "button/icon") {
            QPushButton* lIcon;
            QPushButton* lButton = createButtonIcon(lName, &lIcon);
            if(lPicto != "") {
                if(lPictoColor == "") lPictoColor = "#ffffff";
                lIcon->setIcon(GQTPICTO(lPicto, lPictoColor));
            }
            lButton->setCursor(Qt::PointingHandCursor);
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
int GQtPlan::countSocialNetworksItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/social_networks']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getSocialNetworksItem(int _index, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/social_networks']/map/data[position()=%1]/%2").arg(_index + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
