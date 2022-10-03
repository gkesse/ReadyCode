//===============================================
#ifndef _GModules_
#define _GModules_
//===============================================
#include "GModule.h"
//===============================================
class GModules : public GModule {
public:
    GModules();
    ~GModules();

    GObject* clone() const;

    GString serialize(const GString& _code = "module") const;
    void deserialize(const GString& _data, const GString& _code = "module");

    bool onModule();
    bool onCreateModule();
    bool createModule();
    bool insertModule();

protected:
    int m_id;
    GString m_name;
};
//==============================================
#endif
//==============================================
