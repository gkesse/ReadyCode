//===============================================
#ifndef _GProSQLiteTableButtonUserData_
#define _GProSQLiteTableButtonUserData_
//===============================================
#include "GProUi.h"
//===============================================
class GProSQLiteTableButtonUserData : public GProUi {
    Q_OBJECT
    
public:
    GProSQLiteTableButtonUserData(QWidget* parent = 0);
    ~GProSQLiteTableButtonUserData();

public slots:
	void onEvent(const QString& text);
};
//==============================================
#endif
//==============================================
