//===============================================
#ifndef _GAccountUi_
#define _GAccountUi_
//===============================================
#include "GDialog.h"
//===============================================
class GAccountUi : public GDialog {
	Q_OBJECT

public:
	GAccountUi(QWidget* _parent = 0);
	~GAccountUi();
	void createLayout();
	void onAccountCreate();
    void onUsernameClear();
    void onUsernameClear(const QString& _text);
    void onPasswordClear();
    void onPasswordClear(const QString& _text);
    void onConfirmClear();
    void onConfirmClear(const QString& _text);

public slots:
    void onEvent();
    void onEvent(const QString& _text);
};
//===============================================
#endif
//===============================================
