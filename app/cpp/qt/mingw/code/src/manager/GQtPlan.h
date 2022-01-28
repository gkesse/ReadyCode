//===============================================
#ifndef _GQtPlan_
#define _GQtPlan_
//===============================================
#include "GQtWidget.h"
//===============================================
class GQtPlan : public GQtWidget {
    Q_OBJECT

public:
    GQtPlan(QWidget* _parent = 0);
    ~GQtPlan();
    void createDoms();
    //
    void initSettings();
    QString getSettingItem(const QString& _data) const;
    //
    QLayout* createMainWindow();
    int countMainWindowItems() const;
    QString getMainWindowItem(int _index, const QString& _data) const;
    //
    QWidget* createTitleBar();
    int countTitleBarItems() const;
    QString getTitleBarItem(int _index, const QString& _data) const;
    //
    QWidget* createSearchBar();
    int countSearchBarItems() const;
    QString getSearchBarItem(int _index, const QString& _data) const;

private:

};
//==============================================
#endif
//==============================================
