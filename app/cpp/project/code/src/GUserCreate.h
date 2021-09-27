//===============================================
#ifndef _GUserCreate_
#define _GUserCreate_
//===============================================
#include "GDialogUi.h"
//===============================================
class GUserCreate : public GDialogUi {
    Q_OBJECT
    
public:
    GUserCreate(QWidget* parent = 0);
    ~GUserCreate();
    void setTitle();

public slots:
    void onEvent();
    void onEvent(const QString& text);
    
private:
    QMap<QWidget*, QString> m_widgetMap;
    QLineEdit* m_usernameEdit;
    QLineEdit* m_passwordEdit;
    QLineEdit* m_confirmEdit;
};
//==============================================
#endif
//==============================================
