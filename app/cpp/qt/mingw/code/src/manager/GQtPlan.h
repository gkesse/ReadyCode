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
    QString getTitle() const;
    QString getLogo() const;
    int getWidth() const;
    int getHeight() const;
    bool fullscreenOn() const;
    bool maximizeOn() const;
    //
    QLayout* createMainWindow();
    int countMainWindowItems() const;
    QString getMainWindowItemType(int _index) const;
    QString getMainWindowItemText(int _index) const;
    QString getMainWindowItemFontSize(int _index) const;
    //
    QFrame* createTitleBar();
    int countTitleBarItems() const;
    QString getTitleBarItemType(int _index) const;
    QString getTitleBarItemName(int _index) const;
    QString getTitleBarItemIcon(int _index) const;
    QString getTitleBarItemPicto(int _index) const;
    QString getTitleBarItemPictoColor(int _index) const;
    //
    QFrame* createSearchBar();
    int countSearchBarItems() const;
    QString getSearchBarItemCategory(int _index) const;
    QString getSearchBarItemType(int _index) const;
    QString getSearchBarItemName(int _index) const;
    QString getSearchBarItemIcon(int _index) const;
    QString getSearchBarItemPicto(int _index) const;
    QString getSearchBarItemPictoColor(int _index) const;
    int getSearchBarItemMinWidth(int _index) const;

private:

};
//==============================================
#endif
//==============================================
