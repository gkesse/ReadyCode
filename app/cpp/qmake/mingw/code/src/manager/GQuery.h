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
    GQuery();
    ~GQuery();
    GObject* clone() const;
    GString serialize(const GString& _code = "query");
    void deserialize(const GString& _data, const GString& _code = "query");

    void setTypeId(int _typeId);
    void setTypeName(const GString& _typeName);
    void setEmission(const GString& _emission);
    void setReception(const GString& _reception);

    int getTypeId() const;
    GString getTypeName() const;
    GString getEmission() const;
    GString getReception() const;

    void sendQuery();
    void saveTypeQuery();
    void searchTypeQuery();
    void deleteTypeQuery();

private:
    int m_typeId;
    int m_defaultId;
    GString m_typeName;
    GString m_emission;
    GString m_reception;
};
//==============================================
#endif
//==============================================
