//===============================================
#ifndef _GModuleUi_
#define _GModuleUi_
//===============================================
#include "GInclude.h"
//===============================================
class GModule;
class GModuleData;
class GModuleMap;
//===============================================
namespace Ui {
    class GModuleUi;
}
//===============================================
class GModuleUi : public QFrame {
    Q_OBJECT

public:
    GModuleUi(QWidget* parent = 0);
    ~GModuleUi();

    void resetData();
    void readData();
    void writeData();

    void onTabMap();
    void loadModule();
    void loadModuleMap();

public slots:
    // tab
    void on_tabWidget_tabBarClicked(int _index);
    // module
    void on_btnSave_clicked();
    void on_btnSearch_clicked();
    void on_btnNew_clicked();
    void on_tableModule_itemClicked(QTableWidgetItem* _item);
    void on_tableModule_itemDoubleClicked(QTableWidgetItem* _item);
    // module_data
    void on_btnSaveData_clicked();
    void on_btnSearchData_clicked();
    void on_btnNewData_clicked();
    // module_map
    void on_btnAddMap_clicked();
    void on_btnMoveUpMap_clicked();
    void on_btnMoveDownMap_clicked();

private:
    Ui::GModuleUi *ui;
    std::shared_ptr<GModule> m_module;
    std::shared_ptr<GModuleData> m_moduleData;
    std::shared_ptr<GModuleMap> m_moduleMap;

    int m_moduleId;
    int m_moduleDataId;
    int m_moduleMapId;

    bool m_isVisibleTabData;
    bool m_isVisibleTabMap;
    int m_tabDataIndex;
    int m_tabMapIndex;
};
//==============================================
#endif
//==============================================
