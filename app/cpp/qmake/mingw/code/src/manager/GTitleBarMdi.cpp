//===============================================
#include "GTitleBarMdi.h"
#include "GPath.h"
#include "GPicto.h"
#include "GLog.h"
//===============================================
GTitleBarMdi::GTitleBarMdi(QWidget* _parent)
: GWidget(_parent) {
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

    setObjectName("bottom");
    setLayout(lMainLayout);

    m_mainWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    m_mainWindow->setAttribute(Qt::WA_DeleteOnClose);

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
    m_mainWindow->close();
}
//===============================================
void GTitleBarMdi::onMinimize() {
    QPushButton* lMinimize = (QPushButton*)getObj("minimize");
    QPushButton* lMaximize = (QPushButton*)getObj("maximize");
    //
    if(m_windowState != "minimize") {
        lMinimize->setIcon(GPICTO("windowrestore", "#ffffff"));
        lMaximize->setIcon(GPICTO("windowmaximize", "#ffffff"));
        m_mainWindow->setWindowFlags(Qt::Window);
        m_windowState = "minimize";
        m_mainWindow->showMinimized();
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
        m_mainWindow->showMaximized();
        m_windowState = "maximize";
    }
    else {
        lMinimize->setIcon(GPICTO("windowminimize", "#ffffff"));
        lMaximize->setIcon(GPICTO("windowmaximize", "#ffffff"));
        m_mainWindow->showNormal();
        m_windowState = "normal";
    }
}
//===============================================
void GTitleBarMdi::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        setCursor(QCursor(Qt::SizeAllCursor));
        m_pressPos = event->pos();
        m_pressFlag = true;
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
        m_mainWindow->move(m_diffPos);
    }
}
//===============================================
bool GTitleBarMdi::eventFilter(QObject* _obj, QEvent* _event) {
    if(_obj == m_mainWindow) {
        if(_event->type() == QEvent::WindowStateChange) {
            if(m_mainWindow->isMinimized()) {
                m_minimizeOn = true;
            }
            else if(m_minimizeOn) {
                QPushButton* lMinimize = (QPushButton*)getObj("minimize");
                QPushButton* lMaximize = (QPushButton*)getObj("maximize");
                m_mainWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
                if(m_mainWindow->isMaximized()) {
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
    return QObject::eventFilter(_obj, _event);
}
//===============================================
