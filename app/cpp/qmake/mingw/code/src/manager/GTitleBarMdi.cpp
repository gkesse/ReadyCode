//===============================================
#include "GTitleBarMdi.h"
#include "GPath.h"
#include "GPicto.h"
#include "GLog.h"
//===============================================
GTitleBarMdi::GTitleBarMdi(QWidget* _mdiWindow, QWidget* _parent)
: GWidget(_parent)
, m_mdiWindow(_mdiWindow) {
    createDoms();
    createLayout();
}
//===============================================
GTitleBarMdi::~GTitleBarMdi() {

}
//===============================================
void GTitleBarMdi::createLayout() {
    int lCount = countItem("pad/mdi");
    m_mainWindow = parentWidget();
    m_mdiWindow->installEventFilter(this);

    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(5);
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
        if(lKey == "fullscreen") continue;
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
            lButton->installEventFilter(this);
            addObj(lKey, lButton);
            lButton->setObjectName(lStyle);
            lButton->setText(lText);
            lMainLayout->addWidget(lButton);
            m_mdiWindow->setWindowTitle(lText);
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
            addObj(lKey, lButton);
            lButton->setObjectName(lStyle);
            QIcon lIcon = QIcon(GRES("img", lImg));
            lButton->setIcon(lIcon);
            lButton->setIconSize(QSize(lSize, lSize));
            lButton->setCursor(Qt::PointingHandCursor);
            lMainLayout->addWidget(lButton);
            m_mdiWindow->setWindowIcon(lIcon);
            connect(lButton, SIGNAL(clicked()), this, SLOT(onEvent()));
        }
    }

    setObjectName("flat");
    setLayout(lMainLayout);
    setMinimumHeight(40);

    m_mdiWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    m_mdiWindow->setAttribute(Qt::WA_DeleteOnClose);
    m_mainWindow->setContentsMargins(0,  40,  0,  0);

    m_pressFlag = false;
    m_minimizeOn = false;
    m_windowState = "normal";
}
//===============================================
void GTitleBarMdi::onEvent() {
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
    else {
        onErrorKey(lKey);
    }
    GERROR_SHOWG(eGERR);
}
//===============================================
void GTitleBarMdi::onClose() {
    m_mdiWindow->close();
}
//===============================================
void GTitleBarMdi::onMinimize() {
    QPushButton* lMinimize = (QPushButton*)getObj("minimize");
    QPushButton* lMaximize = (QPushButton*)getObj("maximize");
    //
    if(m_windowState != "minimize") {
        lMinimize->setIcon(GPICTO("windowrestore", "#ffffff"));
        lMaximize->setIcon(GPICTO("windowmaximize", "#ffffff"));
        m_mdiWindow->setWindowFlags(Qt::Window);
        m_windowState = "minimize";
        m_mdiWindow->showMinimized();
    }
}
//===============================================
void GTitleBarMdi::onMaximize() {
    QPushButton* lMinimize = (QPushButton*)getObj("minimize");
    QPushButton* lMaximize = (QPushButton*)getObj("maximize");
    //
    if(m_windowState != "maximize") {
        lMinimize->setIcon(GPICTO("windowminimize", "#ffffff"));
        lMaximize->setIcon(GPICTO("windowrestore", "#ffffff"));
        m_mdiWindow->showMaximized();
        m_windowState = "maximize";
    }
    else {
        lMinimize->setIcon(GPICTO("windowminimize", "#ffffff"));
        lMaximize->setIcon(GPICTO("windowmaximize", "#ffffff"));
        m_mdiWindow->showNormal();
        m_windowState = "normal";
    }
}
//===============================================
void GTitleBarMdi::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        setCursor(QCursor(Qt::SizeAllCursor));
        m_pressPos = event->pos();
        m_pressFlag = true;
        m_diffPos = m_mainWindow->geometry().topLeft();
    }
}
//===============================================
void GTitleBarMdi::mouseReleaseEvent(QMouseEvent* event) {
    setCursor(QCursor(Qt::ArrowCursor));
    m_pressFlag = false;
}
//===============================================
void GTitleBarMdi::mouseMoveEvent(QMouseEvent* event) {
    if(m_pressFlag == true) {
        QPoint lCurrentPos = event->pos();
        QPoint lDiffPos = lCurrentPos - m_pressPos;
        m_diffPos += lDiffPos;
        m_mdiWindow->move(m_diffPos);
    }
}
//===============================================
bool GTitleBarMdi::eventFilter(QObject* _obj, QEvent* _event) {
    QPushButton* lLogo = (QPushButton*)getObj("logo");
    QPushButton* lTitle = (QPushButton*)getObj("title");
    //
    if(_obj == m_mdiWindow) {
        if(_event->type() == QEvent::Resize) {
            setFixedWidth(m_mdiWindow->width());
        }
        else if(_event->type() == QEvent::WindowIconChange) {
            lLogo->setIcon(m_mdiWindow->windowIcon());
        }
        else if(_event->type() == QEvent::WindowTitleChange) {
            lTitle->setText(m_mdiWindow->windowTitle());
        }
        else if(_event->type() == QEvent::WindowStateChange) {
            if(m_mdiWindow->isMinimized()) {
                m_minimizeOn = true;
            }
            else if(m_minimizeOn) {
                QPushButton* lMinimize = (QPushButton*)getObj("minimize");
                QPushButton* lMaximize = (QPushButton*)getObj("maximize");
                m_mdiWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
                if(m_mdiWindow->isMaximized()) {
                    lMinimize->setIcon(GPICTO("windowminimize", "#ffffff"));
                    lMaximize->setIcon(GPICTO("windowrestore", "#ffffff"));
                    m_windowState = "maximize";
                }
                else {
                    lMinimize->setIcon(GPICTO("windowminimize", "#ffffff"));
                    lMaximize->setIcon(GPICTO("windowmaximize", "#ffffff"));
                    m_windowState = "normal";
                }
                m_minimizeOn = false;
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
