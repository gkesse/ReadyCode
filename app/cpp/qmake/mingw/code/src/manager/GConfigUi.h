//===============================================
#ifndef _GConfigUi_
#define _GConfigUi_
//===============================================
#include "GInclude.h"
//===============================================
class GModule;
class GModuleData;
class GModuleKey;
class GModuleMap;
class GModuleType;
class GModuleNode;
class GSearch;
//===============================================
namespace Ui {
    class GConfigUi;
}
//===============================================
class GConfigUi : public QFrame {
    Q_OBJECT

public:
    GConfigUi(QWidget* parent = 0);
    ~GConfigUi();

    void readData();
    void writeData();

public slots:
    // module
    void on_btnSaveModule_clicked();
    void on_btnSearchModule_clicked();
    void on_btnDeleteModule_clicked();
    void on_btnNewModule_clicked();
    // module_data
    void on_btnSaveData_clicked();
    void on_btnSearchData_clicked();
    void on_btnNewData_clicked();
    // module_key
    void onLoadModuleKey();
    void onLoadCmbTypeModuleKey();
    void on_btnSaveKey_clicked();
    void on_btnSearchKey_clicked();
    void on_btnNewKey_clicked();
    // module_map
    void on_btnSaveMap_clicked();
    void on_btnSearchMap_clicked();
    void on_btnNewMap_clicked();
    // module_node
    void onLoadKeyModuleNode();
    // module_type
    void onLoadModuleType();
    void on_btnSaveType_clicked();
    void on_btnSearchType_clicked();
    void on_btnDeleteType_clicked();
    void on_btnNewType_clicked();
    // search
    void onLoadSearchConfig();

private:
    Ui::GConfigUi *ui;
    std::shared_ptr<GModule> m_module;
    std::shared_ptr<GModuleData> m_moduleData;
    std::shared_ptr<GModuleKey> m_moduleKey;
    std::shared_ptr<GModuleMap> m_moduleMap;
    std::shared_ptr<GModuleType> m_moduleType;

    std::shared_ptr<GModuleType> m_moduleTypeList;
    std::shared_ptr<GModuleKey> m_moduleKeyList;
    std::shared_ptr<GSearch> m_searchConfig;

    int m_moduleId;
    int m_moduleDataId;
    int m_moduleKeyId;
    int m_moduleMapId;
    int m_mapPosition;
    int m_moduleTypeId;
};
//==============================================
#endif
//==============================================
