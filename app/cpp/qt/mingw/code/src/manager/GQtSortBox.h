//===============================================
#ifndef _GQtSortBox_
#define _GQtSortBox_
//===============================================
#include "GQtWidget.h"
//===============================================
class GQtSortBox : public GQtWidget {
    Q_OBJECT

public:
    GQtSortBox(QWidget* _parent = 0);
    ~GQtSortBox();
    void setTitle(const QString& _title);
    void clearColumnCombo();
    void addItemColumnCombo(const QString& _item);
    int currentIndexColumnCombo() const;
    int currentIndexOrderCombo() const;

private:
    QGroupBox* m_groupBox;
    QComboBox* m_columnCombo;
    QComboBox* m_orderCombo;
};
//==============================================
#endif
//==============================================
