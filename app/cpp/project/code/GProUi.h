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
	virtual void addPage(const QString& key, const QString& title, QWidget* widget, bool isDefault = 0);
	virtual int loadPage(const QString& key);
	virtual void setPage(const QString& key);
	virtual GProUi* getPage(const QString& key);
	virtual int getPageId(const QString& key);
	virtual QWidget* getWidget(const QString& key);
	virtual QString getTitle(const QString& key);
	virtual QString getDefaultKey();
	virtual void addItem(const QString& key, const QString& text);
	virtual void setAddress(const QString& text);
	virtual void loadData(const QStringList& headers, const QVector<QVector<QString>>& datas);
	virtual QString getKey(const QString& key, const QString& defaultKey);
	virtual void setTitle(const QString& text);
	virtual void setTitle(const QString& key, const QString& title);

public slots:
	virtual void onEvent();
	virtual void onEvent(const QString& text);
	virtual void onEvent(const QPoint& pos);
	virtual void onEvent(int row, int col);
	virtual void onEvent(QTableWidget* tableWidget, int row, int col);

signals:
	void emitEvent();
	void emitEvent(const QString& text);
	void emitEvent(QTableWidget* tableWidget, int row, int col);
};
//==============================================
#endif
//==============================================
