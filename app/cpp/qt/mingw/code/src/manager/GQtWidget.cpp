//===============================================
#include "GQtWidget.h"
#include "GQtWindow.h"
#include "GQtOpenGL.h"
#include "GQtTeamsBox.h"
#include "GQtLog.h"
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
    if(_key == "window") return new GQtWindow(_parent);
    if(_key == "opengl") return new GQtOpenGL(_parent);
    if(_key == "teamsbox") return new GQtTeamsBox(_parent);
    return new GQtWidget(_parent);
}
//===============================================
