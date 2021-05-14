//===============================================
#ifndef _GDatabase_
#define _GDatabase_
//===============================================
#include <iostream>
#include <string>
//===============================================
class GDatabase {
public:
    GDatabase();
    ~GDatabase();

public:
    static GDatabase* Instance();
    void open();
    void load();
    void update();
    void save();
    
private:
    static GDatabase* m_instance;
};
//===============================================
#endif
//===============================================
