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
    QVector<QVector<QString>> readMap(const QString& sql);
    QStringList getFields(const QString& table);

private:
    static GSQLite* m_instance;
};
//==============================================
#endif
//==============================================
