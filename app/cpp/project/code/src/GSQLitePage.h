//===============================================
#ifndef _GSQLiteWin_
#define _GSQLiteWin_
//===============================================
#include "GProUi.h"
//===============================================
class GSQLitePage : public GProUi {
    Q_OBJECT
    
public:
    GSQLitePage(QWidget* parent = 0);
    ~GSQLitePage();
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
