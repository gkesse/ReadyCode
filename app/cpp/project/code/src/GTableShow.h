//===============================================
#ifndef _GTableShow_
#define _GTableShow_
//===============================================
#include "GDialogUi.h"
//===============================================
class GTableShow : public GDialogUi {
    Q_OBJECT
    
public:
    GTableShow(QWidget* parent = 0);
    ~GTableShow();

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
