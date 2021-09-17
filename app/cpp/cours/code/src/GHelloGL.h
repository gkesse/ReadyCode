//===============================================
#ifndef _GHelloGL_
#define _GHelloGL_
//===============================================
#include "GQtUi.h"
//===============================================
class GHelloGLWindow;
//===============================================
class GHelloGL : public GQtUi {
	Q_OBJECT

public:
	GHelloGL(QWidget* parent = 0);
	virtual ~GHelloGL();
	void resize();
	QMainWindow* getWindow();

public slots:
	void onAddNew();

private:
	QMainWindow* mainWindow;
};
//==============================================
#endif
//==============================================
