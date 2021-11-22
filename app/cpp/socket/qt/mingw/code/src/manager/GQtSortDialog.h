//===============================================
#ifndef _GQtSortDialog_
#define _GQtSortDialog_
//===============================================
#include "GQtDialog.h"
#include "GQt.h"
//===============================================
class GQtSortDialog : public GQtDialog {
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
