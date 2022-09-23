//===============================================
#ifndef _GTitleBarApp_
#define _GTitleBarApp_
//===============================================
#include "GWidget.h"
//===============================================
class GPadMdi;
//===============================================
class GTitleBarApp : public GWidget {
    Q_OBJECT

public:
    GTitleBarApp(QWidget* _parent = 0);
    ~GTitleBarApp();
    void createLayout();
    void onClose();
    void onMinimize();
    void onMaximize();
    void onFullscreen();
    void onConnection();
    void setPseudo(const GString& _pseudo);

public slots:
    void onEvent();

protected:
    void mousePressEvent(QMouseEvent* _event);
    void mouseReleaseEvent(QMouseEvent* _event);
    void mouseMoveEvent(QMouseEvent* _event);
    bool eventFilter(QObject* _obj, QEvent* _event);

private:
    GPadMdi* m_mainWindow;
    QString m_windowState;
    QPoint m_pressPos;
    QPoint m_diffPos;
    bool m_pressFlag;
    bool m_minimizeOn;
};
//===============================================
#endif
//===============================================
