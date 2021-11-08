//===============================================
#ifndef _GOpenGLGridParams_
#define _GOpenGLGridParams_
//===============================================
#include "GWidget.h"
//===============================================
class GOpenGLGridParams : public GWidget {
	Q_OBJECT

public:
    GOpenGLGridParams(QWidget* _parent = 0);
    ~GOpenGLGridParams();

public slots:
	void onEvent();
};
//==============================================
#endif
//==============================================
