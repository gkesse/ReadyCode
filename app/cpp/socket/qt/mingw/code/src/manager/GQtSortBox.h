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

private:
    QGroupBox* m_groupBox;
};
//==============================================
#endif
//==============================================
