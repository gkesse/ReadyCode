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
    GQueryType();
    ~GQueryType();
    GObject* clone() const;
    GString serialize(const GString& _code = "query_type");
    void deserialize(const GString& _data, const GString& _code = "query_type");

    void setQueryType(const GQueryType& _queryType);
    void setQueryType(GQueryType* _queryType);
    void setQueryType(int _index);

    void setId(int _id);
    void setName(const GString& _name);

    int getId() const;
    GString getName() const;

    void saveQueryType();
    void searchQueryType();
    void deleteQueryType();

    bool showList();
    bool showNextList();
    void onNextData();

private:
    int m_id;
    GString m_name;
    std::shared_ptr<GTableWidgetUi> m_tableWidget;
};
//==============================================
#endif
//==============================================
