//===============================================
#ifndef _GSchemaShow_
#define _GSchemaShow_
//===============================================
#include "GDialogUi.h"
//===============================================
class GSchemaShow : public GDialogUi {
    Q_OBJECT
    
public:
    GSchemaShow(QWidget* parent = 0);
    ~GSchemaShow();

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
