//===============================================
#ifndef _GProSQLiteTableUserDataAdd_
#define _GProSQLiteTableUserDataAdd_
//===============================================
#include "GProUi.h"
//===============================================
class GProSQLiteTableUserDataAdd : public GProUi {
    Q_OBJECT
    
public:
    GProSQLiteTableUserDataAdd(QWidget* parent = 0);
    ~GProSQLiteTableUserDataAdd();

public slots:
	void onEvent(const QString& text);
};
//==============================================
#endif
//==============================================
