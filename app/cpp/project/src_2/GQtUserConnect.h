//===============================================
#ifndef _GQtUserConnect_
#define _GQtUserConnect_
//===============================================
#include "GQtUi.h"
//===============================================
class GUserConnect : public GQtUi {
    Q_OBJECT
    
public:
    GUserConnect(QWidget* parent = 0);
    ~GUserConnect();

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
