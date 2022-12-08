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
    void addRow(const GString& _key, const GString& _label, const GString& _type = "lineedit");
    void setData(const GString& _key, const GString& _value, const GString& _type = "lineedit");
    GString getData(const GString& _key, const GString& _type = "lineedit") const;
    void clear();

private:
    QWidget* m_widget;
    QFormLayout* m_formLayout;
    QVBoxLayout* m_mainLayout;
    QMap<GString, QWidget*> m_widgetMap;
};
//==============================================
#endif
//==============================================
