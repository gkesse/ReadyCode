//===============================================
#ifndef _GSQLiteTablesShow_
#define _GSQLiteTablesShow_
//===============================================
#include "GInclude.h"
#include "GSQLiteUi.h"
//===============================================
class GSQLiteTablesShow : public GSQLiteUi {
    Q_OBJECT
    
public:
    GSQLiteTablesShow(QObject* parent = 0);
    virtual ~GSQLiteTablesShow();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
