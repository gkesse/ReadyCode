//===============================================
#ifndef _GModule_
#define _GModule_
//===============================================
#include "GSearch.h"
//===============================================
class GTableWidgetUi;
//===============================================
class GModule : public GSearch {
public:
    GModule();
    ~GModule();
    GObject* clone() const;
    GString serialize(const GString& _code = "module") const;
    bool deserialize(const GString& _data, const GString& _code = "module");

    void setModule(const GModule& _module);
    void setModule(GModule* _module);
    void setModule(int _index);
    void setName(const GString& _name);
    int getId() const;
    GString getName() const;

    void saveModule();
    void searchModule();
    void deleteModule();
    void onNextData();
    bool showList();
    bool showNextList();

protected:
    int m_id;
    GString m_name;
    std::vector<GObject*> m_map;
    GTableWidgetUi* m_tableWidget;
};
//==============================================
#endif
//==============================================
