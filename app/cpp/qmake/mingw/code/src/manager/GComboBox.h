//===============================================
#ifndef _GComboBox_
#define _GComboBox_
//===============================================
#include "GObject.h"
//===============================================
class GComboBox : public QComboBox {
    Q_OBJECT

public:
    GComboBox(QWidget* parent = 0);
    ~GComboBox();
    void setIndexData(const std::shared_ptr<GObject>& _obj);
    int getIndexData(const GString& _data) const;
};
//==============================================
#endif
//==============================================
