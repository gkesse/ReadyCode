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
void GComboBox::setIndexData(const GString& _data) {
    setCurrentIndex(getIndexData(_data));
}
//===============================================
int GComboBox::getIndexData(const GString& _data) const {
    int lIndex = findData(_data.c_str());
    if(lIndex == -1) return 0;
    return lIndex;
}
//===============================================
