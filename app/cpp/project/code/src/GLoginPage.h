//===============================================
#ifndef _GLoginPage_
#define _GLoginPage_
//===============================================
#include "GProUi.h"
//===============================================
class GLoginPage : public GProUi {
    Q_OBJECT
    
public:
    GLoginPage(QWidget* parent = 0);
    ~GLoginPage();
    void setTitle();

public slots:
    void onEvent();
    void onEvent(const QString& text);
    
private:
    QMap<QWidget*, QString> m_widgetMap;
    QTextEdit* m_textEdit;
};
//==============================================
#endif
//==============================================
