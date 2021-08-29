//===============================================
#ifndef _GOpenCVUi_
#define _GOpenCVUi_
//===============================================
#include "GInclude.h"
//===============================================
class GOpenCVUi : public QObject {
    Q_OBJECT
    
public:
    GOpenCVUi(QObject* parent = 0);
    virtual ~GOpenCVUi();
    static GOpenCVUi* Create(const QString& key);
    virtual void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
