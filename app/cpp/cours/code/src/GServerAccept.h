//===============================================
#ifndef _GServerAccept_
#define _GServerAccept_
//===============================================
#include "GBoostUi.h"
//===============================================
class GServerAccept : public GBoostUi {
    Q_OBJECT
    
public:
    GServerAccept(QObject* parent = 0);
    virtual ~GServerAccept();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
