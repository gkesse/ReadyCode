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
    void onHelp();

public slots:
    void onEvent();

protected:
    void mousePressEvent(QMouseEvent* _event);
    void mouseReleaseEvent(QMouseEvent* _event);
    void mouseMoveEvent(QMouseEvent* _event);
    bool eventFilter(QObject* _obj, QEvent* _event);

private:
    QDialog* m_mainWindow;
    QPoint m_pressPos;
    QPoint m_diffPos;
    bool m_pressFlag;
};
//===============================================
#endif
//===============================================
