//===============================================
#ifndef _GLoginUi_
#define _GLoginUi_
//===============================================
#include "GDialog.h"
//===============================================
class GUser;
//===============================================
class GLoginUi : public GDialog {
	Q_OBJECT

public:
	GLoginUi(GUser* _user, QWidget* _parent = 0);
	~GLoginUi();
	void createLayout();
	void onConnect();
    void onUsernameClear();
    void onUsernameClear(const QString& _text);
    void onPasswordClear();
    void onPasswordClear(const QString& _text);
    void onAccountCreate();

public slots:
    void onEvent();
    void onEvent(const QString& _text);

private:
    GUser* m_user;
};
//===============================================
#endif
//===============================================
