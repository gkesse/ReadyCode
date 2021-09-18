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
	static GProUi* Create(const QString& key, QWidget* parent = 0);
	virtual void setTitle();
	virtual void setSize();
	virtual void setCenter(QWidget* parent);
	virtual QMap<QString, QString> getData();

public slots:
	virtual void onEvent();
	virtual void onEvent(const QString& text);

protected:
	QMap<QString, QString> m_dataMap;
};
//==============================================
#endif
//==============================================
