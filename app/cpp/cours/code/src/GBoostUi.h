//===============================================
#ifndef _GBoostUi_
#define _GBoostUi_
//===============================================
#include "GInclude.h"
//===============================================
class GBoostUi : public QObject {
    Q_OBJECT
    
public:
    GBoostUi(QObject* parent = 0);
    virtual ~GBoostUi();
    static GBoostUi* Create(const QString& key);
    virtual void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
