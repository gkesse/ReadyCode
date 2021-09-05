//===============================================
#ifndef _GHelloGLDock_
#define _GHelloGLDock_
//===============================================
#include "GInclude.h"
//===============================================
class GHelloGLWidget;
//===============================================
class GHelloGLDock : public QFrame {
    Q_OBJECT
    
public:
    GHelloGLDock(QMainWindow* win, QWidget* parent = 0);
    virtual ~GHelloGLDock();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void dockUndock();

private:
    QSlider *createSlider();

    GHelloGLWidget *glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QPushButton *dockBtn;
    QMainWindow *mainWindow;
};
//==============================================
#endif
//==============================================
