//===============================================
#ifndef _GTitleBarDialog_
#define _GTitleBarDialog_
//===============================================
#include "GWidget.h"
//===============================================
class GTitleBarDialog : public GWidget {
    Q_OBJECT

public:
    GTitleBarDialog(QWidget* _parent = 0);
    ~GTitleBarDialog();
    void createLayout();
    void onClose();
    void onMinimize();
    void onMaximize();
    void onFullscreen();

public slots:
    void onEvent();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

private:
    QWidget* m_mainWindow;
    QPoint m_pressPos;
    bool m_pressFlag;
};
//===============================================
#endif
//===============================================
