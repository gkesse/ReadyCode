//===============================================
#ifndef _GUserConnect_
#define _GUserConnect_
//===============================================
#include "GProUi.h"
//===============================================
class GUserConnect : public GProUi {
    Q_OBJECT
    
public:
    GUserConnect(QWidget* parent = 0);
    ~GUserConnect();
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
