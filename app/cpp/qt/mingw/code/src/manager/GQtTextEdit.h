//===============================================
#ifndef _GQtTextEdit_
#define _GQtTextEdit_
//===============================================
#include "GInclude.h"
//===============================================
class GQtTextEdit : public QTextEdit {
    Q_OBJECT

public:
    GQtTextEdit(QWidget* _parent = 0);
    ~GQtTextEdit();
};
//==============================================
#endif
//==============================================
