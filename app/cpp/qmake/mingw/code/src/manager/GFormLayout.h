//===============================================
#ifndef _GFormLayout_
#define _GFormLayout_
//===============================================
#include "GInclude.h"
//===============================================
class GFormLayout : public QFrame {
    Q_OBJECT

public:
    GFormLayout(QWidget* parent = 0);
    ~GFormLayout();
    void addRow(const GString& _label, QWidget* _field);
    void clear();

private:
    QWidget* m_widget;
    QFormLayout* m_formLayout;
    QVBoxLayout* m_mainLayout;
};
//==============================================
#endif
//==============================================
