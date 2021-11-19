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
GQtWidget* GQtWidget::Create(const QString& _key) {
    if(_key == "default") return new GQtWidget;
    if(_key == "qt/window") return new GQtWindow;
    if(_key == "opengl/interface") return new GQtOpenGL;
    if(_key == "xml/interface") return new GQtXml;
    return new GQtWidget;
}
//===============================================

