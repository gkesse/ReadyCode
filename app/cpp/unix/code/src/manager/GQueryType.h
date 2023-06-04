//===============================================
#ifndef _GQueryType_
#define _GQueryType_
//===============================================
#include "GSearch.h"
//===============================================
class GQueryType : public GSearch {
public:
    GQueryType();
    ~GQueryType();
    GObject* clone() const;
    GString serialize(const GString& _code = "query_type");
    void deserialize(const GString& _data, const GString& _code = "query_type");

    void setId(int _id);
    int getId() const;

    bool onModule();
    bool onSaveQueryType();
    bool onSearchQueryType();
    bool onSearchNextQueryType();
    bool onDeleteQueryType();

    bool saveData();
    bool searchData();
    bool searchNextData();
    bool deleteData();
    bool countSearch();
    bool insertData();
    bool updateData();

protected:
    int m_id;
    GString m_name;
};
//==============================================
#endif
//==============================================
