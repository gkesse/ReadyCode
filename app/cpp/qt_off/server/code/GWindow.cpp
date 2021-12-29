//================================================
#include "GWindow.h"
#include "GWindowGL.h"
//================================================
GWindow::GWindow(QWidget* parent) : QFrame(parent) {    
    GWindowGL* lWindowGL = new GWindowGL;
    QWidget* lWindowGLW = QWidget::createWindowContainer(lWindowGL, this);
    
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(lWindowGLW);
    
    setLayout(lMainLayout);
}
//================================================
GWindow::~GWindow() {

}
//================================================
