//===============================================
#ifndef _GTableWidget_
#define _GTableWidget_
//===============================================
#include "GInclude.h"
//===============================================
class GTableWidget : public QTableWidget {
    Q_OBJECT

public:
    GTableWidget(QWidget* parent = 0);
    ~GTableWidget();

    void setSize(int _rows, int _cols);
    void setHeader(int _col, const GString& _data);
    void setData(int _row, int _col, const GString& _key, const GString& _data);
    void addRow();
    void addCol(int _col, const GString& _key, const GString& _data);
    void setKey(const GString& _key);
    GString getKey() const;

public slots:
    void onItemClicked(QTableWidgetItem* _item);

private:
    GString m_key;
};
//==============================================
#endif
//==============================================
