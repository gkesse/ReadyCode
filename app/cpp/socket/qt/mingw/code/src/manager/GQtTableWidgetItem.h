//===============================================
#ifndef _GQtTableWidgetItem_
#define _GQtTableWidgetItem_
//===============================================
#include "GInclude.h"
//===============================================
class GQtTableWidgetItem : public QTableWidgetItem {
public:
    GQtTableWidgetItem();
    ~GQtTableWidgetItem();
    static GQtTableWidgetItem* Create(const QString& _key);
    virtual void setFormula(const QString& _formula);
    virtual QString getFormula() const;
};
//==============================================
#endif
//==============================================
