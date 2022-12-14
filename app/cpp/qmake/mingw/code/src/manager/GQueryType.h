//===============================================
#ifndef _GQueryType_
#define _GQueryType_
//===============================================
#include "GSearch.h"
//===============================================
class GTableWidgetUi;
//===============================================
class GQueryType : public GSearch {
public:
    GQueryType(const GString& _code = "query_type");
    ~GQueryType();
    GObject* clone() const;
    GString serialize(const GString& _code = "query_type");
    bool deserialize(const GString& _data, const GString& _code = "query_type");

    void setId(int _id);
    void setName(const GString& _name);

    int getId() const;
    GString getName() const;

    void saveQueryType();
    void searchQueryType();
    void deleteQueryType();

private:
    int m_id;
    GString m_name;
};
//==============================================
#endif
//==============================================
