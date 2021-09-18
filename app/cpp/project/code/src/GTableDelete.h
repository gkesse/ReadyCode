//===============================================
#ifndef _GTableDelete_
#define _GTableDelete_
//===============================================
#include "GDialogUi.h"
//===============================================
class GTableDelete : public GDialogUi {
    Q_OBJECT
    
public:
    GTableDelete(QWidget* parent = 0);
    ~GTableDelete();

public slots:
    void onEvent();
    void onEvent(const QString& text);
    
private:
    QMap<QWidget*, QString> m_widgetMap;
    QComboBox* m_table;
};
//==============================================
#endif
//==============================================
