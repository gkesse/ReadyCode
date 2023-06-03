//===============================================
#ifndef _GPocoGetXml_
#define _GPocoGetXml_
//===============================================
#include "GPoco.h"
//===============================================
class GPocoGetXml : public GPoco {
public:
    GPocoGetXml();
    ~GPocoGetXml();
    GString serialize(const GString& _code = "poco");
    void deserialize(const GString& _data, const GString& _code = "poco");

public:
    bool run(const GString& _url);
    bool onGet();

protected:
    GString m_module;
    GString m_method;
};
//==============================================
#endif
//==============================================
