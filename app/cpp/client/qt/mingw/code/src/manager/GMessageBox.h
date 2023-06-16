//===============================================
#ifndef _GMessageBox_
#define _GMessageBox_
//===============================================
#include "GInclude.h"
//===============================================
class GMessageBox : public QMessageBox {
    Q_OBJECT

public:
    GMessageBox(QWidget* _parent = 0);
    ~GMessageBox();
};
//===============================================
#endif
//===============================================
