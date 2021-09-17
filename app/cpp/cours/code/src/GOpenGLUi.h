//===============================================
#ifndef _GOpenGLUi_
#define _GOpenGLUi_
//===============================================
#include "GInclude.h"
//===============================================
class GOpenGLUi : public QObject {
    Q_OBJECT
    
public:
    GOpenGLUi(QObject* parent = 0);
    virtual ~GOpenGLUi();
    static GOpenGLUi* Create(const QString& key);
    virtual void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
