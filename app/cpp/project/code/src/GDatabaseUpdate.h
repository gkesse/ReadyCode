//===============================================
#ifndef _GDatabaseUpdate_
#define _GDatabaseUpdate_
//===============================================
#include "GProUi.h"
//===============================================
class GDatabaseUpdate : public GProUi {
    Q_OBJECT
    
public:
    GDatabaseUpdate(QWidget* parent = 0);
    ~GDatabaseUpdate();
    void setTitle();

public slots:
    void onEvent();
    void onEvent(const QString& text);
    
private:
    QMap<QWidget*, QString> m_widgetMap;
    QLineEdit* m_usernameEdit;
    QLineEdit* m_passwordEdit;
};
//==============================================
#endif
//==============================================
