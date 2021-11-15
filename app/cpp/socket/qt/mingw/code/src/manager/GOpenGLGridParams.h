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
    void dataIn(std::string& _dataIn);
    void call(const std::string& _dataIn, std::string& _dataOut);

public slots:
    void onEvent();
};
//==============================================
#endif
//==============================================
