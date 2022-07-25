//===============================================
#ifndef _GPadUi_
#define _GPadUi_
//===============================================
#include "GWidget.h"
//===============================================
class GUser;
//===============================================
class GPadUi : public GWidget {
	Q_OBJECT

public:
	GPadUi(QWidget* _parent = 0);
	~GPadUi();
    void createLayout();

public slots:
	void onEvent();
	void onEvent(const QString& _text);

protected:
	bool eventFilter(QObject* _obj, QEvent* _event);

private:
	GUser* m_user;
};
//===============================================
#endif
//===============================================
