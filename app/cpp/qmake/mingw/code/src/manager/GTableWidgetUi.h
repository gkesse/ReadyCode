//===============================================
#ifndef _GTableWidgetUi_
#define _GTableWidgetUi_
//===============================================
#include "GInclude.h"
//===============================================
class GSearch;
//===============================================
namespace Ui {
    class GTableWidgetUi;
}
//===============================================
class GTableWidgetUi : public QDialog {
    Q_OBJECT

public:
    GTableWidgetUi(QWidget* parent = 0);
    ~GTableWidgetUi();

    void initTableWidget();
    void setSearch(GSearch* _search);
    void setSize(int _rows, int _cols);
    void setHeader(int _col, const GString& _data);
    void setData(int _row, int _col, const GString& _key, const GString& _data);
    void addRow();
    void addCol(int _col, const GString& _key, const GString& _data);
    int getIndex() const;
    GString getKey() const;

public slots:
    void on_btnSelect_clicked();
    void on_btnNext_clicked();
    void on_tableWidget_cellClicked(int row, int column);
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void on_tableWidget_cellDoubleClicked(int row, int column);


private:
    Ui::GTableWidgetUi *ui;
    int m_index;
    GString m_key;
    GSearch* m_search;
};
//==============================================
#endif
//==============================================
