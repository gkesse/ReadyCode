//===============================================
#ifndef _GSQLiteDbUpdate_
#define _GSQLiteDbUpdate_
//===============================================
#include "GInclude.h"
#include "GSQLiteUi.h"
//===============================================
class GSQLiteDbUpdate : public GSQLiteUi {
    Q_OBJECT
    
public:
    GSQLiteDbUpdate(QObject* parent = 0);
    virtual ~GSQLiteDbUpdate();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
