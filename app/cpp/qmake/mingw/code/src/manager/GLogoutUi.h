//===============================================
#ifndef _GLogoutUi_
#define _GLogoutUi_
//===============================================
#include "GMessageBox.h"
//===============================================
class GConnection;
//===============================================
class GLogoutUi : public GMessageBox {
	Q_OBJECT

public:
	GLogoutUi(GConnection* _connection, QWidget* _parent = 0);
	~GLogoutUi();
	int exec();

private:
	GConnection* m_connection;
};
//===============================================
#endif
//===============================================
