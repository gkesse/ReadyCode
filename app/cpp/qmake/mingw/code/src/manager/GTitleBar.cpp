//===============================================
#include "GTitleBar.h"
#include "GPadMdi.h"
#include "GStyle.h"
#include "GPath.h"
#include "GPicto.h"
//===============================================
GTitleBar::GTitleBar() :
GWidget() {
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
    m_mainWindow->installEventFilter(this);

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
        if(lKey == "connection") continue;
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
        else if(lModel == "button/picto") {
            QPushButton* lButton = new QPushButton;
            addObj(lKey, lButton);
            lButton->setObjectName(lStyle);
            lButton->setIcon(GPICTO(lPicto, lPictoColor));
            lButton->setIconSize(QSize(lSize, lSize));
            lButton->setText(lText);
            lButton->setCursor(Qt::PointingHandCursor);
            lMainLayout->addWidget(lButton);
            connect(lButton, SIGNAL(clicked()), this, SLOT(onEvent()));
        }
        else if(lModel == "button/title") {
            QPushButton* lButton = new QPushButton;
            lButton->installEventFilter(this);
            addObj(lKey, lButton);
            lButton->setObjectName(lStyle);
            lButton->setText(lText);
            lMainLayout->addWidget(lButton);
            m_mainWindow->setWindowTitle(lText);
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
            lButton->setIcon(QIcon(GPATH("img", lImg)));
            lButton->setIconSize(QSize(lSize, lSize));
            lButton->setCursor(Qt::PointingHandCursor);
            lMainLayout->addWidget(lButton);
            connect(lButton, SIGNAL(clicked()), this, SLOT(onEvent()));
        }
        else if(lModel == "img/logo") {
            QPushButton* lButton = new QPushButton;
            addObj(lKey, lButton);
            lButton->setObjectName(lStyle);
            QIcon lIcon = QIcon(GPATH("img", lImg));
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
    setMinimumHeight(40);

    m_mainWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    m_mainWindow->setAttribute(Qt::WA_DeleteOnClose);
    m_mainWindow->setContentsMargins(10,  40,  10,  10);

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
        lFullscreen->setIcon(QIcon(GPATH("img", "fullscreen")));
        lMaximize->setIcon(GPICTO("windowrestore", "#ffffff"));
        m_windowState = "maximize";
        m_mainWindow->showMaximized();
    }
    else {
        lFullscreen->setIcon(QIcon(GPATH("img", "fullscreen")));
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
        lFullscreen->setIcon(QIcon(GPATH("img", "fullscreen_exit")));
        lMaximize->setIcon(GPICTO("windowmaximize", "#ffffff"));
        m_windowState = "fullscreen";
        m_mainWindow->showFullScreen();
    }
    else {
        lFullscreen->setIcon(QIcon(GPATH("img", "fullscreen")));
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
        m_diffPos = m_mainWindow->geometry().topLeft();
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
bool GTitleBar::eventFilter(QObject* _obj, QEvent* _event) {
    QPushButton* lLogo = (QPushButton*)getObj("logo");
    QPushButton* lTitle = (QPushButton*)getObj("title");
    //
    if(_obj == m_mainWindow) {
        if(_event->type() == QEvent::Resize) {
            setFixedWidth(m_mainWindow->width());
        }
        else if(_event->type() == QEvent::WindowIconChange) {
            lLogo->setIcon(m_mainWindow->windowIcon());
        }
        else if(_event->type() == QEvent::WindowTitleChange) {
            lTitle->setText(m_mainWindow->windowTitle());
        }
        else if(_event->type() == QEvent::WindowStateChange) {
            QPushButton* lFullscreen = (QPushButton*)getObj("fullscreen");
            QPushButton* lMaximize = (QPushButton*)getObj("maximize");
            //
            if(m_mainWindow->isMaximized()) {
                lFullscreen->setIcon(QIcon(GPATH("img", "fullscreen")));
                lMaximize->setIcon(GPICTO("windowrestore", "#ffffff"));
                m_windowState = "maximize";
            }
            else if(m_mainWindow->isFullScreen()) {
                lFullscreen->setIcon(QIcon(GPATH("img", "fullscreen_exit")));
                lMaximize->setIcon(GPICTO("windowmaximize", "#ffffff"));
                m_windowState = "fullscreen";
            }
        }
    }
    else if(_obj == lTitle) {
        if(_event->type() == QEvent::MouseButtonPress) {
            QMouseEvent* lEvent = (QMouseEvent*)_event;
            if(lEvent->button() == Qt::LeftButton) {
                mousePressEvent(lEvent);
            }
        }
        else if(_event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent* lEvent = (QMouseEvent*)_event;
            if(lEvent->button() == Qt::LeftButton) {
                mouseReleaseEvent(lEvent);
            }
        }
    }
    return QObject::eventFilter(_obj, _event);
}
//===============================================
