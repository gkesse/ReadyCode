//===============================================
#ifndef _GProList_
#define _GProList_
//===============================================
#include "GProUi.h"
//===============================================
class GProList : public GProUi {
    Q_OBJECT

public:
    GProList(QWidget* parent = 0);
    ~GProList();
    void addItem(QString key, QString text);
    
public slots:
    void slotEvent();
    
private:
    QVBoxLayout* m_scrollLayout;
    QMap<QWidget*, QString> m_widgetId;
};
//===============================================
#endif
//===============================================
