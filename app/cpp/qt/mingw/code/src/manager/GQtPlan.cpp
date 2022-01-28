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
    QVBoxLayout* lContentLayout = new QVBoxLayout;
    lContentLayout->setAlignment(Qt::AlignTop);
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
    }

    QFrame* lContentPage = new QFrame;
    lContentPage->setLayout(lContentLayout);

    QScrollArea* lMainPage = new QScrollArea;
    lMainPage->setWidget(lContentPage);
    lMainPage->setWidgetResizable(true);
    lMainPage->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(lMainPage);
    lMainLayout->setAlignment(Qt::AlignTop);
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
    QHBoxLayout* lTopLayout = new QHBoxLayout;
    lTopLayout->setMargin(0);
    lTopLayout->setSpacing(10);

    QHBoxLayout* lCenterLayout = new QHBoxLayout;
    lCenterLayout->setMargin(0);
    lCenterLayout->setSpacing(10);

    int lCount = countSearchBarItems();

    for(int i = 0; i < lCount; i++) {
        QString lCategory = getSearchBarItem(i, "category");
        QString lType = getSearchBarItem(i, "type");
        QString lName = getSearchBarItem(i, "name");
        QString lIcon = getSearchBarItem(i, "icon");
        QString lPicto = getSearchBarItem(i, "picto");
        QString lPictoColor = getSearchBarItem(i, "picto_color");
        int lMinWidth = getSearchBarItem(i, "min_width").toInt();

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
