//===============================================
#ifndef _GModule_
#define _GModule_
//===============================================
#include "GSearch.h"
//===============================================
class GTableWidgetUi;
class GTableWidgetFr;
class GTableWidget;
//===============================================
class GModule : public GSearch {
public:
    GModule(const GString& _code = "module");
    ~GModule();
    GObject* clone() const;
    GString serialize(const GString& _code = "module") const;
    bool deserialize(const GString& _data, const GString& _code = "module");

    void setModule(const GModule& _module);
    void setModule(GModule* _module);
    void setModule(int _index);

    void setId(int _id);
    void setName(const GString& _name);

    int getId() const;
    GString getName() const;

    void loadModule();
    void loadModule2();
    void saveModule();
    void searchModule();
    void deleteModule();

    bool showModule(GTableWidget* _tableWidget);
    bool showModule2(GTableWidgetFr* _tableWidget);
    bool showList();
    bool showNextList();
    void onNextData();

protected:
    int m_id;
    GString m_name;
    std::vector<GObject*> m_map;
    GTableWidgetUi* m_tableWidget;
};
//==============================================
#endif
//==============================================
