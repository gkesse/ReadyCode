//===============================================
#ifndef _GClass_
#define _GClass_
//===============================================
#include "GInclude.h"
//===============================================
class GClass {
public:
    GClass();
    virtual ~GClass();
    void addObserver(GClass* _obs);
    void notify();
    virtual void update();
    virtual void on();

protected:
    std::vector<GClass*> m_obs;
};
//===============================================
#endif
//===============================================
