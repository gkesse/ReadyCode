//===============================================
#ifndef _GTreeWidgetUi_
#define _GTreeWidgetUi_
//===============================================
#include "GInclude.h"
//===============================================
class GTreeWidgetUi : public QTreeWidget {
    Q_OBJECT

public:
    GTreeWidgetUi(QWidget* parent = 0);
    ~GTreeWidgetUi();

    void addHeader();
    void addRoot();
    void initRoot();
    void addChild();
    void setData(int _col, const GString& _key, const GString& _data);
    void setKey(const GString& _key);
    GString getKey() const;

public slots:
    void onItemClicked(QTreeWidgetItem* _item, int _column);

private:
    GString m_key;
    QTreeWidgetItem* m_header;
    QTreeWidgetItem* m_root;
    QTreeWidgetItem* m_child;
    QTreeWidgetItem* m_node;
};
//==============================================
#endif
//==============================================
