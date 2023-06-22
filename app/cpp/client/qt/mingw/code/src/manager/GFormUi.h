//===============================================
#ifndef _GFormUi_
#define _GFormUi_
//===============================================
#include "GDialog.h"
//===============================================
namespace Ui {
class GFormUi;
}
//===============================================
class GFormUi : public GDialog {
    Q_OBJECT

public:
    GFormUi(QWidget* _parent = 0);
    ~GFormUi();
    GFormUi* clone();
    void setObj(const GFormUi& _obj);
    bool isEqual(const GDialog& _obj) const;
    void setValue(const GString& _value);
    GString getValue() const;
    GFormUi& loadFromMap(int i);
    GFormUi& loadToMap(int i);
    void addItem(const GString& _data);
    void addLineEdit(const GString& _label, const GString& _value = "");
    void addComboBox(const GString& _label, const GString& _value = "", int _index = 1);
    void loadData();
    int run();
    GString serialize(const GString& _code = "forms") const;
    void deserialize(const GString& _data, const GString& _code = "forms");

private:
    Ui::GFormUi* ui;
    int m_index;
    GString m_model;
    GString m_label;
    GString m_value;
    std::vector<QWidget*> m_fields;
};
//===============================================
#endif
//===============================================
