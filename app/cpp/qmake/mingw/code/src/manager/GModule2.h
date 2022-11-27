//===============================================
#ifndef _GModule2_
#define _GModule2_
//===============================================
#include "GSearch.h"
//===============================================
class GTableWidgetUi;
class GTableWidgetFr;
class GTableWidget;
//===============================================
class GModule2 : public GSearch {
public:
    GModule2(const GString& _code = "module");
    ~GModule2();
    GObject* clone() const;
    GString serialize(const GString& _code = "module");
    bool deserialize(const GString& _data, const GString& _code = "module");

    void setModule(const GModule2& _module);

    void setId(int _id);
    void setName(const GString& _name);

    int getId() const;
    GString getName() const;

    void saveModule();
    void searchModule();
    void deleteModule();

    bool showModule(GTableWidget* _tableWidget);
    bool showList();
    bool showNextList();
    void onNextData();

protected:
    int m_id;
    GString m_name;
    std::vector<GObject*> m_map;
    std::shared_ptr<GTableWidgetUi> m_tableWidget;
};
//==============================================
#endif
//==============================================
