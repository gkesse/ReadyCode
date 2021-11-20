//===============================================
#include "GQtWidget.h"
#include "GQtWindow.h"
#include "GQtOpenGL.h"
#include "GQtXml.h"
//===============================================
GQtWidget::GQtWidget(QWidget* _parent) :
QFrame(_parent) {

}
//===============================================
GQtWidget::~GQtWidget() {

}
//===============================================
GQtWidget* GQtWidget::Create(const QString& _key, QWidget* _parent) {
    if(_key == "default") return new GQtWidget(_parent);
    if(_key == "qt/window") return new GQtWindow(_parent);
    if(_key == "opengl/interface") return new GQtOpenGL(_parent);
    if(_key == "xml/interface") return new GQtXml(_parent);
    return new GQtWidget(_parent);
}
//===============================================

