//===============================================
#ifndef _GTreeWidgetUi_
#define _GTreeWidgetUi_
//===============================================
#include "GInclude.h"
//===============================================
class GSearch;
class GTreeWidget;
//===============================================
namespace Ui {
    class GTreeWidgetUi;
}
//===============================================
class GTreeWidgetUi : public QDialog {
    Q_OBJECT

public:
    GTreeWidgetUi(QWidget* parent = 0);
    ~GTreeWidgetUi();
    void setSearch(GSearch* _search);
    GTreeWidget* getTreeWidget();
    GString getKey() const;

public slots:
    void on_btnSelect_clicked();
    void on_btnNext_clicked();
    void on_treeWidget_itemClicked(QTreeWidgetItem* _item, int _column);
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem* _item, int _column);

private:
    Ui::GTreeWidgetUi *ui;
    GSearch* m_search;
    GString m_key;
};
//==============================================
#endif
//==============================================
