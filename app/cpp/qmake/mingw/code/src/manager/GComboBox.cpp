//===============================================
#include "GComboBox.h"
//===============================================
GComboBox::GComboBox(QWidget* _parent)
: QComboBox(_parent) {

}
//===============================================
GComboBox::~GComboBox() {

}
//===============================================
void GComboBox::setIndexData(const std::shared_ptr<GObject>& _obj) {
    setCurrentIndex(getIndexData(_obj->serialize()));
}
//===============================================
int GComboBox::getIndexData(const GString& _data) const {
    int lIndex = findData(_data.c_str());
    if(lIndex == -1) return 0;
    return lIndex;
}
//===============================================
