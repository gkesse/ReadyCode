//===============================================
#ifndef _GLogMsg_
#define _GLogMsg_
//===============================================
#include "GMessageBox.h"
//===============================================
class GLogMsg : public GMessageBox {
    Q_OBJECT

public:
    GLogMsg(QWidget* _parent = 0);
    ~GLogMsg();
};
//===============================================
#endif
//===============================================
