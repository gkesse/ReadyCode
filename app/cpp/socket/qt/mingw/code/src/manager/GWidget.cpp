//===============================================
#include <GQtOpenGL.h>
#include <GQtXml.h>
#include "GWidget.h"
//===============================================
GWidget::GWidget(QWidget* _parent) :
QFrame(_parent) {

}
//===============================================
GWidget::~GWidget() {

}
//===============================================
GWidget* GWidget::Create(const QString& _key) {
    if(_key == "default") return new GWidget;
    if(_key == "opengl/interface") return new GQtOpenGL;
    if(_key == "xml/interface") return new GQtXml;
    return new GWidget;
}
//===============================================
void GWidget::onEvent() {}
//===============================================
