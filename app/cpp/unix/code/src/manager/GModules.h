//===============================================
#ifndef _GModules_
#define _GModules_
//===============================================
#include "GModule2.h"
//===============================================
class GModules : public GModule2 {
public:
    GModules();
    ~GModules();

    GObject* clone() const;

    GString serialize(const GString& _code = "module") const;
    bool deserialize(const GString& _data, const GString& _code = "module");

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
