//===============================================
#ifndef _GProSQLiteTableUserDataButton_
#define _GProSQLiteTableUserDataButton_
//===============================================
#include "GProUi.h"
//===============================================
class GProSQLiteTableUserDataButton : public GProUi {
    Q_OBJECT
    
public:
    GProSQLiteTableUserDataButton(QWidget* parent = 0);
    ~GProSQLiteTableUserDataButton();

public slots:
	void onEvent(const QString& text);
};
//==============================================
#endif
//==============================================
