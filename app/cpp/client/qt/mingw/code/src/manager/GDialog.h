//===============================================
#ifndef _GDialog_
#define _GDialog_
//===============================================
#include "GInclude.h"
#include "GLog.h"
//===============================================
class GDialog : public QDialog {
    Q_OBJECT

public:
    GDialog(QWidget* _parent = 0);
    ~GDialog();

protected:
    GLog m_logs;
};
//===============================================
#endif
//===============================================
