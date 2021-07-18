//===============================================
#ifndef _GQtUserConnect_
#define _GQtUserConnect_
//===============================================
#include "GQtUi.h"
//===============================================
class GQtUserConnect : public GQtUi {
    Q_OBJECT
    
public:
    GQtUserConnect(QWidget* parent = 0);
    ~GQtUserConnect();
    void onEvent(const QString& event);

public slots:
    void slotEvent();
    
private:
    QMap<QWidget*, QString> m_widgetMap;
    QLineEdit* m_usernameEdit;
    QLineEdit* m_passwordEdit;
};
//==============================================
#endif
//==============================================
