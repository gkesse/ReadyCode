//===============================================
#ifndef _GPocoPostXml_
#define _GPocoPostXml_
//===============================================
#include "GPoco.h"
//===============================================
class GPocoPostXml : public GPoco {
public:
    GPocoPostXml();
    ~GPocoPostXml();
    GString serialize(const GString& _code = "poco");
    void deserialize(const GString& _data, const GString& _code = "poco");

public:
    bool run(const GString& _url);
    bool onPost();

protected:
    GString m_module;
    GString m_method;
};
//==============================================
#endif
//==============================================
