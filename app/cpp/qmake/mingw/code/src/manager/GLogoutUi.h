//===============================================
#ifndef _GLogoutUi_
#define _GLogoutUi_
//===============================================
#include "GMessageBox.h"
//===============================================
class GUser;
//===============================================
class GLogoutUi : public GMessageBox {
	Q_OBJECT

public:
	GLogoutUi(GUser* _user, QWidget* _parent = 0);
	~GLogoutUi();
	int exec();

private:
    GUser* m_user;
};
//===============================================
#endif
//===============================================
