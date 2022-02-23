//===============================================
#ifndef _GLogin_
#define _GLogin_
//===============================================
#include "GWidget.h"
//===============================================
class GLogin : public GWidget {
	Q_OBJECT

public:
	GLogin(QWidget* _parent = 0);
	~GLogin();
	void createDoms();
	QString getItem(const QString& _data) const;
};
//===============================================
#endif
//===============================================
