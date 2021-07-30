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
	void onEvent();

private:
    QLineEdit* m_usernameEdit;
    QLineEdit* m_passwordEdit;
    QLineEdit* m_confirmEdit;
};
//==============================================
#endif
//==============================================
