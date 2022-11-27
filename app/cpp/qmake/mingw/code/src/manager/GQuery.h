//===============================================
#ifndef _GQuery_
#define _GQuery_
//===============================================
#include "GSearch.h"
//===============================================
class GTableWidgetUi;
//===============================================
class GQuery : public GSearch {
public:
    GQuery(const GString& _code = "query");
    ~GQuery();
    GObject* clone() const;
    GString serialize(const GString& _code = "query");
    bool deserialize(const GString& _data, const GString& _code = "query");

    void setEmission(const GString& _emission);
    void setReception(const GString& _reception);
    GString getEmission() const;
    GString getReception() const;

    void sendQuery();

private:
    GString m_emission;
    GString m_reception;
};
//==============================================
#endif
//==============================================
