//===============================================
#ifndef _GQtTableWidget_
#define _GQtTableWidget_
//===============================================
#include "GInclude.h"
//===============================================
class GQtTableWidget : public QTableWidget {
    Q_OBJECT

public:
    GQtTableWidget(QWidget* _parent = 0);
    ~GQtTableWidget();
};
//==============================================
#endif
//==============================================
