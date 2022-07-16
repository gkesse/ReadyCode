//===============================================
#include "GTitleBar.h"
#include "GPadMdi.h"
#include "GStyle.h"
#include "GPath.h"
#include "GPicto.h"
//===============================================
GTitleBar::GTitleBar(QWidget* _parent) :
GWidget(_parent) {
    createDoms();
    createLayout();
}
//===============================================
GTitleBar::~GTitleBar() {

}
//===============================================
void GTitleBar::createLayout() {
    int lCount = countItem("pad/mdi");
    m_mainWindow = parentWidget();

    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setContentsMargins(5,  5,  5,  5);
    lMainLayout->setSpacing(0);

    for(int i = 0; i < lCount; i++) {
        QString lCategory = getItem("pad/mdi", "category", i);
        QString lModel = getItem("pad/mdi", "model", i);
        QString lStyle = getItem("pad/mdi", "style", i);
        QString lText = getItem("pad/mdi", "text", i);
        QString lImg = getItem("pad/mdi", "img", i);
        QString lPicto = getItem("pad/mdi", "picto", i);
        QString lPictoColor = getItem("pad/mdi", "picto_color", i);
        QString lKey = getItem("pad/mdi", "key", i);
        int lSize = getItem("pad/mdi", "size", i).toInt();
        //
        if(lKey == "help") continue;
        //
        if(lModel == "spacer") {
            lMainLayout->addStretch();
        }
        else if(lModel == "button") {
            QPushButton* lButton = new QPushButton;
            addObj(lKey, lButton);
            lButton->setObjectName(lStyle);
            lButton->setText(lText);
            lMainLayout->addWidget(lButton);
            connect(lButton, SIGNAL(clicked()), this, SLOT(onEvent()));
        }
        else if(lModel == "button/title") {
            QPushButton* lButton = new QPushButton;
            addObj(lKey, lButton);
            lButton->setObjectName(lStyle);
            lButton->setText(lText);
            lButton->setCursor(Qt::PointingHandCursor);
            lMainLayout->addWidget(lButton);
            m_mainWindow->setWindowTitle(lText);
            connect(lButton, SIGNAL(clicked()), this, SLOT(onEvent()));
        }
        else if(lModel == "picto") {
            QPushButton* lButton = new QPushButton;
            addObj(lKey, lButton);
            lButton->setObjectName(lStyle);
            lButton->setIcon(GPICTO(lPicto, lPictoColor));
            lButton->setIconSize(QSize(lSize, lSize));
            lButton->setCursor(Qt::PointingHandCursor);
            lMainLayout->addWidget(lButton);
            connect(lButton, SIGNAL(clicked()), this, SLOT(onEvent()));
        }
        else if(lModel == "img") {
            QPushButton* lButton = new QPushButton;
            addObj(lKey, lButton);
            lButton->setObjectName(lStyle);
            lButton->setIcon(QIcon(GRES("img", lImg)));
            lButton->setIconSize(QSize(lSize, lSize));
            lButton->setCursor(Qt::PointingHandCursor);
            lMainLayout->addWidget(lButton);
            connect(lButton, SIGNAL(clicked()), this, SLOT(onEvent()));
        }
        else if(lModel == "img/logo") {
            QPushButton* lButton = new QPushButton;
            lButton->setObjectName(lStyle);
            QIcon lIcon = QIcon(GRES("img", lImg));
            lButton->setIcon(lIcon);
            lButton->setIconSize(QSize(lSize, lSize));
            lButton->setCursor(Qt::PointingHandCursor);
            lMainLayout->addWidget(lButton);
            m_mainWindow->setWindowIcon(lIcon);
            connect(lButton, SIGNAL(clicked()), this, SLOT(onEvent()));
        }
    }

    setObjectName("flat");
    setLayout(lMainLayout);

    m_mainWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    m_pressFlag = false;
    m_windowState = "normal";
    m_minimizeOn = false;
}
//===============================================
void GTitleBar::onEvent() {
    QString lKey = getKey(sender());
    //
    if(lKey == "close") {
        onClose();
    }
    else if(lKey == "minimize") {
        onMinimize();
    }
    else if(lKey == "maximize") {
        onMaximize();
    }
    else if(lKey == "fullscreen") {
        onFullscreen();
    }
}
//===============================================
void GTitleBar::onClose() {
    m_mainWindow->close();
}
//===============================================
void GTitleBar::onMinimize() {
    m_mainWindow->showMinimized();
}
//===============================================
void GTitleBar::onMaximize() {
    QPushButton* lFullscreen = (QPushButton*)getObj("fullscreen");
    QPushButton* lMaximize = (QPushButton*)getObj("maximize");
    //
    if(m_windowState != "maximize") {
        lFullscreen->setIcon(QIcon(GRES("img", "fullscreen")));
        lMaximize->setIcon(GPICTO("windowrestore", "#ffffff"));
        m_windowState = "maximize";
        m_mainWindow->showMaximized();
    }
    else {
        lFullscreen->setIcon(QIcon(GRES("img", "fullscreen")));
        lMaximize->setIcon(GPICTO("windowmaximize", "#ffffff"));
        m_windowState = "normal";
        m_mainWindow->showNormal();
    }
}
//===============================================
void GTitleBar::onFullscreen() {
    QPushButton* lFullscreen = (QPushButton*)getObj("fullscreen");
    QPushButton* lMaximize = (QPushButton*)getObj("maximize");
    //
    if(m_windowState != "fullscreen") {
        lFullscreen->setIcon(QIcon(GRES("img", "fullscreen_exit")));
        lMaximize->setIcon(GPICTO("windowmaximize", "#ffffff"));
        m_windowState = "fullscreen";
        m_mainWindow->showFullScreen();
    }
    else {
        lFullscreen->setIcon(QIcon(GRES("img", "fullscreen")));
        lMaximize->setIcon(GPICTO("windowmaximize", "#ffffff"));
        m_windowState = "normal";
        m_mainWindow->showNormal();
    }
}
//===============================================
void GTitleBar::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        setCursor(QCursor(Qt::SizeAllCursor));
        m_pressPos = event->pos();
        m_pressFlag = true;
    }
}
//===============================================
void GTitleBar::mouseReleaseEvent(QMouseEvent* event) {
    setCursor(QCursor(Qt::ArrowCursor));
    m_pressFlag = false;
}
//===============================================
void GTitleBar::mouseMoveEvent(QMouseEvent* event) {
    if(m_pressFlag == true) {
        QPoint lCurrentPos = event->pos();
        QPoint lDiffPos = lCurrentPos - m_pressPos;
        m_diffPos += lDiffPos;
        m_mainWindow->move(m_diffPos);
    }
}
//===============================================
