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
	virtual void addPage(QString key, QString title, QWidget* widget, bool isDefault = 0);
	virtual int loadPage();
	virtual void setPage(QString key);
	virtual GProUi* getPage(QString key);
	virtual int getPageId(QString key);
	virtual QWidget* getWidget(QString key);
	virtual QString getTitle(QString key);
	virtual QString getDefaultKey();
	virtual void addItem(QString key, QString text);
	virtual void setContent(QString text);
	virtual void loadData(QStringList headers, QVector<QVector<QString>> datas);
	virtual QString getKey(const QString& key, const QString& defaultKey);

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
