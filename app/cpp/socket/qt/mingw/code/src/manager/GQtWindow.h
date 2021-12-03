//===============================================
#ifndef _GQtWindow_
#define _GQtWindow_
//===============================================
#include "GQtWidget.h"
//===============================================
class GQtSpreadWindow;
//===============================================
class GQtWindow : public GQtWidget {
    Q_OBJECT

public:
    GQtWindow(QWidget* _parent = 0);
    ~GQtWindow();

public slots:
    void onOpenButton();

private:
    GQtSpreadWindow* m_GQtSpreadWindow;
};
//==============================================
#endif
//==============================================
