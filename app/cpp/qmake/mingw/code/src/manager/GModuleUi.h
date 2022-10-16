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

    void readData();
    void writeData();

    void onTabMap();

    void loadModuleMap();

public slots:
    // qtabwidget
    void on_tabWidget_tabBarClicked(int _index);
    // module
    void on_btnSave_clicked();
    void on_btnSearch_clicked();
    void on_btnNew_clicked();
    // module_data
    void on_btnSaveData_clicked();
    void on_btnSearchData_clicked();
    void on_btnNewData_clicked();
    // module_map
    void on_btnAddMap_clicked();
    void on_btnMoveUpMap_clicked();
    void on_btnMoveDownMap_clicked();
    void on_btnSaveMap_clicked();
    void on_btnSearchMap_clicked();
    void on_btnNewMap_clicked();

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
