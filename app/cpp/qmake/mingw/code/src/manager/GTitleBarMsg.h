//===============================================
#ifndef _GTitleBarMsg_
#define _GTitleBarMsg_
//===============================================
#include "GWidget.h"
//===============================================
class GTitleBarMsg : public GWidget {
    Q_OBJECT

public:
    GTitleBarMsg(QWidget* _parent = 0);
    ~GTitleBarMsg();
    void createLayout();
    void onClose();
    void onHelp();

public slots:
    void onEvent();

protected:
    void mousePressEvent(QMouseEvent* _event);
    void mouseReleaseEvent(QMouseEvent* _event);
    void mouseMoveEvent(QMouseEvent* _event);
    bool eventFilter(QObject* _obj, QEvent* _event);

private:
    QMessageBox* m_mainWindow;
    QPoint m_pressPos;
    QPoint m_diffPos;
    bool m_pressFlag;
};
//===============================================
#endif
//===============================================
