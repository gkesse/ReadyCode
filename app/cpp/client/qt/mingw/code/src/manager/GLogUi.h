//===============================================
#ifndef _GLogUi_
#define _GLogUi_
//===============================================
#include "GMessageBox.h"
//===============================================
class GLogUi : public GMessageBox {
    Q_OBJECT

public:
    GLogUi(QWidget* _parent = 0);
    ~GLogUi();
};
//===============================================
#endif
//===============================================
