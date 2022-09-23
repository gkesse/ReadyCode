//===============================================
#ifndef _GLoginUi_
#define _GLoginUi_
//===============================================
#include "GDialog.h"
//===============================================
class GConnection;
//===============================================
class GLoginUi : public GDialog {
	Q_OBJECT

public:
	GLoginUi(GConnection* _connection, QWidget* _parent = 0);
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
    GConnection* m_connection;
};
//===============================================
#endif
//===============================================
