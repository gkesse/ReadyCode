//===============================================
#ifndef _GQtSortBox_
#define _GQtSortBox_
//===============================================
#include "GInclude.h"
//===============================================
class GQtSortBox : public QWidget {
    Q_OBJECT

public:
    GQtSortBox(QWidget* _parent = 0);
    ~GQtSortBox();
    void setTitle(const QString& _title);

protected:
    QGroupBox* m_groupBox;
};
//==============================================
#endif
//==============================================
