//===============================================
#ifndef _GSQLiteFieldsShow_
#define _GSQLiteFieldsShow_
//===============================================
#include "GInclude.h"
#include "GSQLiteUi.h"
//===============================================
class GSQLiteFieldsShow : public GSQLiteUi {
    Q_OBJECT
    
public:
    GSQLiteFieldsShow(QObject* parent = 0);
    virtual ~GSQLiteFieldsShow();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
