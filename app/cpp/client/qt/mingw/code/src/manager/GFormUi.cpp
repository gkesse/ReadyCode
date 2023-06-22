//===============================================
#include "GFormUi.h"
#include "ui_GFormUi.h"
#include "GCode.h"
//===============================================
GFormUi::GFormUi(QWidget *parent)
: GDialog(parent)
, ui(new Ui::GFormUi) {
    ui->setupUi(this);
    m_index = 0;
}
//===============================================
GFormUi::~GFormUi() {
    delete ui;
    clear();
}
//===============================================
GFormUi* GFormUi::clone() {
    return new GFormUi;
}
//===============================================
void GFormUi::setObj(const GFormUi& _obj) {
    m_model = _obj.m_model;
    m_label = _obj.m_label;
    m_value = _obj.m_value;
    m_index = _obj.m_index;
}
//===============================================
bool GFormUi::isEqual(const GDialog& _obj) const {
    const GFormUi& lObj = dynamic_cast<const GFormUi&>(_obj);
    bool lEqualOk = true;
    lEqualOk &= (m_value == lObj.m_value);
    return lEqualOk;
}
//===============================================
void GFormUi::setValue(const GString& _value) {
    m_value = _value;
}
//===============================================
GString GFormUi::getValue() const {
    return m_value;
}
//===============================================
GFormUi& GFormUi::loadFromMap(int i) {
    if(i >= 1 && i <= size()) {
        GFormUi* lObj = (GFormUi*)m_map[i - 1];
        setObj(*lObj);
    }
    return *this;
}
//===============================================
GFormUi& GFormUi::loadToMap(int i) {
    if(i >= 1 && i <= size()) {
        GFormUi* lObj = (GFormUi*)m_map[i - 1];
        lObj->setObj(*this);
    }
    return *this;
}
//===============================================
void GFormUi::addItem(const GString& _data) {
    GFormUi* lObj = new GFormUi;
    lObj->m_model = "item";
    lObj->m_value = _data;
    m_map.push_back(lObj);
}
//===============================================
void GFormUi::addLineEdit(const GString& _label, const GString& _value) {
    GFormUi* lObj = new GFormUi;
    lObj->m_model = "line_edit";
    lObj->m_label = _label;
    lObj->m_value = _value;
    m_map.push_back(lObj);
}
//===============================================
void GFormUi::addComboBox(const GString& _label, const GString& _value, int _index) {
    GFormUi* lObj = new GFormUi;
    lObj->m_model = "combo_box";
    lObj->m_label = _label;
    lObj->m_value = _value;
    lObj->m_index = _index;
    m_map.push_back(lObj);
}
//===============================================
void GFormUi::loadData() {
    for(int i = 0; i < size(); i++) {
        GFormUi* lObj = (GFormUi*)m_map[i];
        if(lObj->m_model == "line_edit") {
            QLineEdit* lField = (QLineEdit*)m_fields[i];
            lObj->m_value = lField->text();
        }
        else if(lObj->m_model == "combo_box") {
            QComboBox* lField = (QComboBox*)m_fields[i];
            lObj->m_value = lField->currentText();
        }
    }
}
//===============================================
int GFormUi::run() {
    if(!size()) return QDialog::Rejected;
    for(int i = 0; i < size(); i++) {
        GFormUi* lObj = (GFormUi*)m_map[i];
        if(lObj->m_model == "line_edit") {
            QLabel* lLabel = new QLabel;
            lLabel->setText(lObj->m_label.c_str());
            QLineEdit* lField = new QLineEdit;
            m_fields.push_back(lField);
            ui->formLayout->addRow(lLabel, lField);
        }
        else if(lObj->m_model == "combo_box") {
            QLabel* lLabel = new QLabel;
            lLabel->setText(lObj->m_label.c_str());
            QComboBox* lField = new QComboBox;
            if(!lObj->m_value.isEmpty()) {
                GFormUi lItems;
                lItems.deserialize(lObj->m_value);
                for(int i = 1; i <= lItems.size(); i++) {
                    GString lItem = lItems.loadFromMap(i).m_value;
                    lField->addItem(lItem.c_str());
                }
                if(lObj->m_index >= 1) {
                    lField->setCurrentIndex(lObj->m_index - 1);
                }
            }
            m_fields.push_back(lField);
            ui->formLayout->addRow(lLabel, lField);
        }
    }
    int lResult = exec();
    if(lResult != QDialog::Rejected) {
        loadData();
    }
    return lResult;
}
//===============================================
GString GFormUi::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "model", m_model);
    lDom.addData(_code, "label", m_label);
    lDom.addData(_code, "value", m_value.toBase64());
    lDom.addData(_code, "index", m_index);
    lDom.addMap(_code, m_map);
    return lDom.toString();
}
//===============================================
void GFormUi::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_model = lDom.getData(_code, "model");
    m_label = lDom.getData(_code, "label");
    m_value = lDom.getData(_code, "value").fromBase64();
    m_index = lDom.getData(_code, "index").toInt();
    lDom.getMap(_code, m_map, this);
}
//===============================================
