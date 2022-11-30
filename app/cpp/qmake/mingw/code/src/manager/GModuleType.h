//===============================================
#ifndef _GModuleType_
#define _GModuleType_
//===============================================
#include "GSearch.h"
//===============================================
class GTableWidgetUi;
class GTableWidget;
//===============================================
class GModuleType : public GSearch {
public:
    GModuleType(const GString& _code = "module_type");
    ~GModuleType();
    GObject* clone() const;
    GString serialize(const GString& _code = "module_type");
    bool deserialize(const GString& _data, const GString& _code = "module_type");

    void setModuleType(const GModuleType& _moduleType);
    void setModuleType(GModuleType* _moduleType);
    void setModuleType(const std::shared_ptr<GModuleType>& _moduleType);
    void setModuleType(int _index);

    void setId(int _id);
    void setName(const GString& _name);

    int getId() const;
    GString getName() const;

    void saveModuleType();
    void searchModuleType();
    void deleteModuleType();

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
