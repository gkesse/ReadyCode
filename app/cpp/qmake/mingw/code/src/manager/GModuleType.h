//===============================================
#ifndef _GModuleType_
#define _GModuleType_
//===============================================
#include "GSearch.h"
//===============================================
class GTableWidgetUi;
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
    void setModuleType(int _index);

    void setId(int _id);
    void setName(const GString& _name);

    int getId() const;
    GString getName() const;

    void loadModuleType();
    void saveModuleType();
    void searchModuleType();
    void deleteModuleType();

    void loadComboBox(QComboBox* _comboBox);

    bool showList();
    bool showNextList();
    void onNextData();

protected:
    int m_id;
    GString m_name;
    std::shared_ptr<GTableWidgetUi> m_tableWidget;
};
//==============================================
#endif
//==============================================
