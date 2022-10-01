//===============================================
#include "GTitleBarDialog.h"
#include "GPath.h"
#include "GPicto.h"
#include "GLog.h"
//===============================================
GTitleBarDialog::GTitleBarDialog(QWidget* _parent)
: GWidget(_parent) {
    createDoms();
    createLayout();
}
//===============================================
GTitleBarDialog::~GTitleBarDialog() {

}
//===============================================
void GTitleBarDialog::createLayout() {
    int lCount = countItem("pad/mdi");
    m_mainWindow = (QDialog*)parentWidget();
    m_mainWindow->installEventFilter(this);

    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setContentsMargins(5, 5, 5, 5);
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
        if(lKey == "minimize") continue;
        if(lKey == "maximize") continue;
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
            lMainLayout->addWidget(lButton);
            m_mainWindow->setWindowIcon(lIcon);
        }
    }

    setObjectName("flat");
    setLayout(lMainLayout);
    setMinimumHeight(40);

    m_mainWindow->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    m_mainWindow->setAttribute(Qt::WA_DeleteOnClose);
    m_mainWindow->setContentsMargins(0,  40,  0,  0);

    m_pressFlag = false;
}
//===============================================
void GTitleBarDialog::onEvent() {
    QString lKey = getKey(sender());
    //
    if(lKey == "close") {
        onClose();
    }
    else if(lKey == "help") {
        onHelp();
    }
    else {
        onErrorKey(lKey);
    }
    GERROR_SHOWG(eGERR);
}
//===============================================
void GTitleBarDialog::onClose() {
    m_mainWindow->close();
}
//===============================================
void GTitleBarDialog::onHelp() {
    QWhatsThis::enterWhatsThisMode();
}
//===============================================
void GTitleBarDialog::mousePressEvent(QMouseEvent* _event) {
    if(_event->button() == Qt::LeftButton) {
        setCursor(QCursor(Qt::SizeAllCursor));
        m_pressPos = _event->pos();
        m_pressFlag = true;
        m_diffPos = m_mainWindow->geometry().topLeft();
    }
    QWidget::mousePressEvent(_event);
}
//===============================================
void GTitleBarDialog::mouseReleaseEvent(QMouseEvent* _event) {
    if(_event->button() == Qt::LeftButton) {
        setCursor(QCursor(Qt::ArrowCursor));
        m_pressFlag = false;
    }
    QWidget::mouseReleaseEvent(_event);
}
//===============================================
void GTitleBarDialog::mouseMoveEvent(QMouseEvent* _event) {
    if(m_pressFlag == true) {
        QPoint lCurrentPos = _event->pos();
        QPoint lDiffPos = lCurrentPos - m_pressPos;
        m_diffPos += lDiffPos;
        m_mainWindow->move(m_diffPos);
    }
    QWidget::mouseMoveEvent(_event);
}
//===============================================
bool GTitleBarDialog::eventFilter(QObject* _obj, QEvent* _event) {
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
