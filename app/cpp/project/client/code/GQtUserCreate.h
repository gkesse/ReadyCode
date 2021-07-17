//===============================================
#ifndef _GQtUserCreate_
#define _GQtUserCreate_
//===============================================
#include "GQtUi.h"
//===============================================
class GQtUserCreate : public GQtUi {
    Q_OBJECT
    
public:
    GQtUserCreate(QWidget* parent = 0);
    virtual ~GQtUserCreate();

public slots:
    void slotClick();
    
private: 
    QLineEdit* m_usernameEdit;
    QLineEdit* m_passwordEdit;
    QLineEdit* m_confirmEdit;
};
//==============================================
#endif
//==============================================
