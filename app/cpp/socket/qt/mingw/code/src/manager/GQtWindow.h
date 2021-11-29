//===============================================
#ifndef _GQtWindow_
#define _GQtWindow_
//===============================================
#include "GQtWidget.h"
//===============================================
class GQtMainWindow;
//===============================================
class GQtWindow : public GQtWidget {
    Q_OBJECT

public:
    GQtWindow(QWidget* _parent = 0);
    ~GQtWindow();

public slots:
    void onOpenButton();

private:
    GQtMainWindow* m_window;
};
//==============================================
#endif
//==============================================
