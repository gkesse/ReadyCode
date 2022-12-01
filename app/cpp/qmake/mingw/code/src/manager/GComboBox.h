//===============================================
#ifndef _GComboBox_
#define _GComboBox_
//===============================================
#include "GInclude.h"
//===============================================
class GComboBox : public QComboBox {
    Q_OBJECT

public:
    GComboBox(QWidget* parent = 0);
    ~GComboBox();
    int getIndexData(const GString& _data) const;
};
//==============================================
#endif
//==============================================
