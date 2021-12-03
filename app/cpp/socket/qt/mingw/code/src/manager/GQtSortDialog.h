//===============================================
#ifndef _GQtSortDialog_
#define _GQtSortDialog_
//===============================================
#include "GInclude.h"
//===============================================
class GQtSortDialog : public QDialog {
    Q_OBJECT

public:
    GQtSortDialog(QWidget* _parent = 0);
    ~GQtSortDialog();

public slots:
    void onMoreButton();
};
//==============================================
#endif
//==============================================
