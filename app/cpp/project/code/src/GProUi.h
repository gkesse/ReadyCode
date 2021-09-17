//===============================================
#ifndef _GProUi_
#define _GProUi_
//===============================================
#include "GInclude.h"
//===============================================
class GProUi : public QFrame {
	Q_OBJECT

public:
	GProUi(QWidget* parent = 0);
	virtual ~GProUi();
	static GProUi* Create(const QString& key);
	virtual void setTitle();
	virtual void setSize();

public slots:
	virtual void onEvent();
	virtual void onEvent(const QString& text);
};
//==============================================
#endif
//==============================================
