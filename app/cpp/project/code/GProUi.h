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
	virtual void onEvent(const QString& event);
	virtual void addPage(QString key, QString title, QWidget* widget, bool isDefault = 0);
	virtual int loadPage();
	virtual void setPage(QString key);
	virtual GProUi* getPage(QString key);
	virtual int getPageId(QString key);
	virtual QWidget* getWidget(QString key);
	virtual QString getTitle(QString key);
	virtual QString getDefaultKey();
	virtual void addItem(QString key, QString text);

public slots:
	virtual void slotEvent();
	virtual void slotEvent(const QString& text);
	virtual void slotEvent(const QPoint& pos);
	virtual void slotEvent(int row, int col);

signals:
	void emitEvent();
	void emitEvent(const QString& text);
};
//==============================================
#endif
//==============================================
