//===============================================
#ifndef _GQuery_
#define _GQuery_
//===============================================
#include "GSearch.h"
//===============================================
class GQuery : public GSearch {
public:
    GQuery();
    ~GQuery();
    GObject* clone() const;
    GString serialize(const GString& _code = "query");
    void deserialize(const GString& _data, const GString& _code = "query");

    bool onModule();
    bool onSendQuery();

private:
    GString m_emission;
    GString m_reception;
};
//==============================================
#endif
//==============================================
