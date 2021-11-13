//===============================================
#include "GWidget.h"
#include "GOpenGLGridParams.h"
//===============================================
GWidget::GWidget(QWidget* _parent) :
QFrame(_parent) {

}
//===============================================
GWidget::~GWidget() {

}
//===============================================
GWidget* GWidget::Create(const QString& _key) {
    if(_key == "widget") return new GWidget;
    if(_key == "opengl/grid/params") return new GOpenGLGridParams;
    return new GWidget;
}
//===============================================
void GWidget::onEvent() {}
//===============================================
