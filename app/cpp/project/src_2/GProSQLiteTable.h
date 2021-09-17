//===============================================
#ifndef _GProSQLiteTable_
#define _GProSQLiteTable_
//===============================================
#include "GProUi.h"
//===============================================
class GProSQLiteTable : public GProUi {
    Q_OBJECT
    
public:
    GProSQLiteTable(QWidget* parent = 0);
    ~GProSQLiteTable();
    int loadPage(const QString& key);

private:
	QMap<QWidget*, QString> m_widgetMap;
    GProUi* m_table;
    GProUi* m_buttonStack;
};
//==============================================
#endif
//==============================================
