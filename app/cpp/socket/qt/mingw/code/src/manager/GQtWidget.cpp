//===============================================
#include "GQtWidget.h"
#include "GQtWindow.h"
#include "GQtOpenGL.h"
#include "GQtXml.h"
#include "GQtSortBox.h"
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
    if(_key == "opengl/ui") return new GQtOpenGL(_parent);
    if(_key == "xml/ui") return new GQtXml(_parent);
    if(_key == "widget/sortbox") return new GQtSortBox(_parent);
    return new GQtWidget(_parent);
}
//===============================================
void GQtWidget::setTitle(const QString& _title) {}
//===============================================

