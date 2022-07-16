//===============================================
#ifndef _GTitleBarMdi_
#define _GTitleBarMdi_
//===============================================
#include "GWidget.h"
//===============================================
class GTitleBarMdi : public GWidget {
    Q_OBJECT

public:
    GTitleBarMdi(QWidget* _parent = 0);
    ~GTitleBarMdi();
    void createLayout();
    void onClose();
    void onMinimize();
    void onMaximize();

public slots:
    void onEvent();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    bool eventFilter(QObject* _obj, QEvent* _event);

private:
    QWidget* m_mainWindow;
    QPoint m_pressPos;
    QPoint m_diffPos;
    bool m_pressFlag;
    QString m_windowState;
    bool m_minimizeOn;
};
//===============================================
#endif
//===============================================
