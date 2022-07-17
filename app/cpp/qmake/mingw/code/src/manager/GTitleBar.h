//===============================================
#ifndef _GTitleBar_
#define _GTitleBar_
//===============================================
#include "GWidget.h"
//===============================================
class GTitleBar : public GWidget {
    Q_OBJECT

public:
    GTitleBar(QWidget* _parent = 0);
    ~GTitleBar();
    void createLayout();
    void onClose();
    void onMinimize();
    void onMaximize();
    void onFullscreen();

public slots:
    void onEvent();

protected:
    void mousePressEvent(QMouseEvent* _event);
    void mouseReleaseEvent(QMouseEvent* _event);
    void mouseMoveEvent(QMouseEvent* _event);
    bool eventFilter(QObject* _obj, QEvent* _event);

private:
    QWidget* m_mainWindow;
    QString m_windowState;
    QPoint m_pressPos;
    QPoint m_diffPos;
    bool m_pressFlag;
    bool m_minimizeOn;
};
//===============================================
#endif
//===============================================
