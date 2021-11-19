//===============================================
#ifndef _GQtFindDialog_
#define _GQtFindDialog_
//===============================================
#include "GQtDialog.h"
//===============================================
class GQtFindDialog : public GQtDialog {
    Q_OBJECT

public:
    GQtFindDialog(QWidget* _parent = 0);
    ~GQtFindDialog();

public slots:
	void onFindButton();
	void onFindEdit(const QString& _text);
};
//==============================================
#endif
//==============================================
