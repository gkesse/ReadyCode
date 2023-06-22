//===============================================
#include "GDialog.h"
//===============================================
GDialog::GDialog(QWidget* _parent)
: QDialog(_parent) {

}
//===============================================
GDialog::~GDialog() {

}
GDialog* GDialog::clone() {
    return new GDialog;
}
//===============================================
void GDialog::clear() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GDialog* lObj = m_map[i];
        delete lObj;
    }
    m_map.clear();
}
//===============================================
void GDialog::setObj(const GDialog& _obj) {

}
//===============================================
GDialog& GDialog::loadFromMap(int i) {
    if(i >= 1 && i <= size()) {
        GDialog* lObj = m_map[i - 1];
        setObj(*lObj);
    }
    return *this;
}
//===============================================
GDialog& GDialog::loadToMap(int i) {
    if(i >= 1 && i <= size()) {
        GDialog* lObj = m_map[i - 1];
        lObj->setObj(*this);
    }
    return *this;
}
//===============================================
bool GDialog::isEqual(const GDialog& _obj) const {
    return false;
}
//===============================================
int GDialog::indexOf(const GDialog& _obj) const {
    for(int i = 0; i < size(); i++) {
        GDialog* lObj = m_map[i];
        if(lObj->isEqual(_obj)) {
            return (i + 1);
        }
    }
    return 0;
}
//===============================================
int GDialog::size() const {
    return (int)m_map.size();
}
//===============================================
void GDialog::print() const {
    printf("%s\n", serialize().c_str());
}
//===============================================
GString GDialog::serialize(const GString& _code) const {
    return "";
}
//===============================================
void GDialog::deserialize(const GString& _data, const GString& _code) {

}
//===============================================
