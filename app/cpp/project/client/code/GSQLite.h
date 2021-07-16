//===============================================
#ifndef _GSQLite_
#define _GSQLite_
//===============================================
#include "GInclude.h"
//===============================================
class GSQLite {
private:
    GSQLite();
    
public:
    ~GSQLite();
    static GSQLite* Instance();
    void open();
    void writeData(const QString& sql);
    QString readData(const QString& sql);
    
private:
    static GSQLite* m_instance;
};
//==============================================
#endif
//==============================================
