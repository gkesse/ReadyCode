//===============================================
#ifndef _GSQLiteUi_
#define _GSQLiteUi_
//===============================================
#include "GInclude.h"
//===============================================
class GSQLiteUi : public QObject {
    Q_OBJECT
    
public:
    GSQLiteUi(QObject* parent = 0);
    virtual ~GSQLiteUi();
    static GSQLiteUi* Create(const QString& key);
    virtual void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
