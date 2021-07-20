//===============================================
#ifndef _GProSQLite_
#define _GProSQLite_
//===============================================
#include "GProUi.h"
//===============================================
class GProSQLite : public GProUi {
    Q_OBJECT
    
public:
    GProSQLite(QWidget* parent = 0);
    ~GProSQLite();

public slots:
	void onEvent();
	void onEvent(const QString& text);
	void onEvent(QTableWidget* tableWidget, int row, int col);

private:
	QMap<QWidget*, QString> m_widgetMap;
};
//==============================================
#endif
//==============================================
