//===============================================
#include "GQtWindow.h"
#include "GSocket.h"
#include "GXml.h"
#include "GDefine.h"
#include "GQt.h"
#include "GStruct.h"
//===============================================
GQtWindow::GQtWindow(QWidget* _parent) :
GQtWidget(_parent) {
    sGQt lParams;
    GQt lSpinBox, lSlider, lMainLayout;
    lSpinBox.createQSpinBox();
    lSpinBox.setRangeQSpinBox(0, 130);
    lSlider.createQSlider();
    lSlider.setRangeQSlider(0,  130);
    lMainLayout.createQHBoxLayout();

}
//===============================================
GQtWindow::~GQtWindow() {

}
//===============================================
