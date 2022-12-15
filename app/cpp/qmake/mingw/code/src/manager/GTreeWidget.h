//===============================================
#ifndef _GTreeWidget_
#define _GTreeWidget_
//===============================================
#include "GInclude.h"
//===============================================
class GTreeWidget : public QTreeWidget {
    Q_OBJECT

public:
    GTreeWidget(QWidget* parent = 0);
    ~GTreeWidget();

    void addHeader();
    void addRoot();
    void initRoot();
    void addChild();
    void setData(int _col, const GString& _key, const GString& _data);
    void selectItem();

private:
    QTreeWidgetItem* m_header;
    QTreeWidgetItem* m_root;
    QTreeWidgetItem* m_child;
    QTreeWidgetItem* m_node;
};
//==============================================
#endif
//==============================================
