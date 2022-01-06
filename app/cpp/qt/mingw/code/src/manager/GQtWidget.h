//===============================================
#ifndef _GQtWidget_
#define _GQtWidget_
//===============================================
#include "GInclude.h"
//===============================================
class GQtWidget : public QFrame {
    Q_OBJECT

public:
    GQtWidget(QWidget* _parent = 0);
    ~GQtWidget();
};
//==============================================
#endif
//==============================================
