//===============================================
#include "GQtPlan.h"
#include "GQtXml.h"
#include "GQtPicto.h"
#include "GQtLog.h"
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
    setWindowTitle(getTitle());
    setWindowIcon(QIcon(GQTRES("studio/img", getLogo())));
    resize(getWidth(), getHeight());
    if(maximizeOn()) {
        showMaximized();
    }
    else if(fullscreenOn()) {
        showFullScreen();
    }
}
//===============================================
QString GQtPlan::getTitle() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/settings']/title");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtPlan::getLogo() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/settings']/logo");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GQtPlan::getWidth() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/settings']/width");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData.toInt();
}
//===============================================
int GQtPlan::getHeight() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/settings']/height");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData.toInt();
}
//===============================================
bool GQtPlan::fullscreenOn() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/settings']/fullscreen_on");
    m_dom->getNodeXPath();
    bool lData = (m_dom->getNodeValue() == "1");
    return lData;
}
//===============================================
bool GQtPlan::maximizeOn() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/settings']/maximize_on");
    m_dom->getNodeXPath();
    bool lData = (m_dom->getNodeValue() == "1");
    return lData;
}
//===============================================
QLayout* GQtPlan::createMainWindow() {
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->setAlignment(Qt::AlignTop);
    lMainLayout->setSpacing(20);

    int lCount = countMainWindowItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getMainWindowItemType(i);
        QString lText = getMainWindowItemText(i);
        QString lFontSize = getMainWindowItemFontSize(i);

        if(lType == "titlebar") {
            lMainLayout->addWidget(createTitleBar());
        }
        else if(lType == "searchbar") {
            lMainLayout->addWidget(createSearchBar());
        }
        else if(lType == "message") {
            QLabel* lLabel = new QLabel;
            lLabel->setText(lText);
            lLabel->setAlignment(Qt::AlignCenter);
            QString lStyle = "";
            if(lFontSize != "") {
                lStyle += QString("QLabel {font-size: %1px;}").arg(lFontSize);
            }
            lLabel->setStyleSheet(lStyle);
            lLabel->setScaledContents(true);
            lMainLayout->addWidget(lLabel);
        }
    }

    return lMainLayout;
}
//===============================================
int GQtPlan::countMainWindowItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/mainwindow']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getMainWindowItemType(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/mainwindow']/map/data[position()=%1]/type").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtPlan::getMainWindowItemText(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/mainwindow']/map/data[position()=%1]/text").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtPlan::getMainWindowItemFontSize(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/mainwindow']/map/data[position()=%1]/font_size").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QFrame* GQtPlan::createTitleBar() {
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countTitleBarItems();

    for(int i = 0; i < lCount; i++) {
        QString lType = getTitleBarItemType(i);
        QString lName = getTitleBarItemName(i);
        QString lIcon = getTitleBarItemIcon(i);
        QString lPicto = getTitleBarItemPicto(i);
        QString lPictoColor = getTitleBarItemPictoColor(i);

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

    QFrame* lMainPage = new QFrame;
    lMainPage->setLayout(lMainLayout);

    return lMainPage;
}
//===============================================
int GQtPlan::countTitleBarItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/titlebar']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getTitleBarItemType(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/titlebar']/map/data[position()=%1]/type").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtPlan::getTitleBarItemName(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/titlebar']/map/data[position()=%1]/name").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtPlan::getTitleBarItemIcon(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/titlebar']/map/data[position()=%1]/icon").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtPlan::getTitleBarItemPicto(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/titlebar']/map/data[position()=%1]/picto").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtPlan::getTitleBarItemPictoColor(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/titlebar']/map/data[position()=%1]/picto_color").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QFrame* GQtPlan::createSearchBar() {
    QHBoxLayout* lTopLayout = new QHBoxLayout;
    lTopLayout->setMargin(0);
    lTopLayout->setSpacing(10);

    QHBoxLayout* lCenterLayout = new QHBoxLayout;
    lCenterLayout->setMargin(0);
    lCenterLayout->setSpacing(10);

    int lCount = countSearchBarItems();

    for(int i = 0; i < lCount; i++) {
        QString lCategory = getSearchBarItemCategory(i);
        QString lType = getSearchBarItemType(i);
        QString lName = getSearchBarItemName(i);
        QString lIcon = getSearchBarItemIcon(i);
        QString lPicto = getSearchBarItemPicto(i);
        QString lPictoColor = getSearchBarItemPictoColor(i);
        int lMinWidth = getSearchBarItemMinWidth(i);

        if(lCategory == "top") {
            if(lType == "radiobutton") {
                QRadioButton* lButton = new QRadioButton;
                lButton->setText(lName);
                lButton->setCursor(Qt::PointingHandCursor);
                lTopLayout->addWidget(lButton);
            }
            else if(lType == "spacer") {
                lTopLayout->addStretch();
            }
        }
        else if(lCategory == "center") {
            if(lType == "button/icon") {
                QPushButton* lIcon;
                QPushButton* lButton = createButtonIcon(lName, &lIcon);
                if(lPicto != "") {
                    if(lPictoColor == "") lPictoColor = "#ffffff";
                    lIcon->setIcon(GQTPICTO(lPicto, lPictoColor));
                }
                lButton->setCursor(Qt::PointingHandCursor);
                lCenterLayout->addWidget(lButton);
            }
            else if(lType == "button") {
                QPushButton* lButton = new QPushButton;
                lButton->setText(lName);
                if(lPicto != "") {
                    if(lPictoColor == "") lPictoColor = "#ffffff";
                    lButton->setIcon(GQTPICTO(lPicto, lPictoColor));
                }
                lButton->setCursor(Qt::PointingHandCursor);
                lCenterLayout->addWidget(lButton);
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
                lCenterLayout->addWidget(lLineEdit);
            }
            else if(lType == "spacer") {
                lCenterLayout->addStretch();
            }
        }
    }

    QVBoxLayout* lContentLayout = new QVBoxLayout;
    lContentLayout->addLayout(lTopLayout);
    lContentLayout->addLayout(lCenterLayout);
    lContentLayout->setMargin(0);
    lContentLayout->setSpacing(20);
    lContentLayout->setSizeConstraint(QLayout::SetMinimumSize);

    QFrame* lContentPage = new QFrame;
    lContentPage->setObjectName("plan_search");
    lContentPage->setLayout(lContentLayout);

    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->addWidget(lContentPage);
    lMainLayout->setMargin(0);
    lMainLayout->setAlignment(Qt::AlignCenter);

    QFrame* lMainPage = new QFrame;
    lMainPage->setLayout(lMainLayout);

    return lMainPage;
}
//===============================================
int GQtPlan::countSearchBarItems() const {
    m_dom->queryXPath("/rdv/datas/data[code='app/searchbar']/map/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtPlan::getSearchBarItemCategory(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/searchbar']/map/data[position()=%1]/category").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtPlan::getSearchBarItemType(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/searchbar']/map/data[position()=%1]/type").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtPlan::getSearchBarItemName(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/searchbar']/map/data[position()=%1]/name").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtPlan::getSearchBarItemIcon(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/searchbar']/map/data[position()=%1]/icon").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtPlan::getSearchBarItemPicto(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/searchbar']/map/data[position()=%1]/picto").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtPlan::getSearchBarItemPictoColor(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/searchbar']/map/data[position()=%1]/picto_color").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GQtPlan::getSearchBarItemMinWidth(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='app/searchbar']/map/data[position()=%1]/min_width").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData.toInt();
}
//===============================================
