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
    QWidget* createMainWindow(int _index);
    int countMainWindowItems() const;
    int countMainWindowItems(int _index) const;
    QString getMainWindowItem(int _index, const QString& _data) const;
    QString getMainWindowItem(int _i, int _j, const QString& _data) const;
    //
    QWidget* createTitleBar();
    int countTitleBarItems() const;
    QString getTitleBarItem(int _index, const QString& _data) const;
    //
    QWidget* createSearchBar();
    int countSearchBarItems() const;
    QString getSearchBarItem(int _index, const QString& _data) const;
    //
    QWidget* createQuickAccess();
    int countQuickAccessItems() const;
    QString getQuickAccessItem(int _index, const QString& _data) const;
    //
    QWidget* createRecentSearch();
    QWidget* createRecentSearch(int _index);
    int countRecentSearchItems() const;
    int countRecentSearchItems(int _index) const;
    QString getRecentSearchItem(int _index, const QString& _data) const;
    QString getRecentSearchItem(int _i, int _j, const QString& _data) const;
    //
    QWidget* createTopCategory();
    int countTopCategoryItems() const;
    QString getTopCategoryItem(int _index, const QString& _data) const;
    //
    QWidget* createHoliday();
    int countHolidayItems() const;
    QString getHolidayItem(int _index, const QString& _data) const;
    //
    QWidget* createLocationMap();
    int countLocationMapItems() const;
    QString getLocationMapItem(int _index, const QString& _data) const;
    //
    QWidget* createCommunity();
    int countCommunityItems() const;
    QString getCommunityItem(int _index, const QString& _data) const;
    //
    QWidget* createMotivation();
    int countMotivationItems() const;
    QString getMotivationItem(int _index, const QString& _data) const;
    //
    QWidget* createQuickLink();
    int countQuickLinkItems() const;
    QString getQuickLinkItem(int _index, const QString& _data) const;
    //
    QWidget* createAbout();
    int countAboutItems() const;
    QString getAboutItem(int _index, const QString& _data) const;
    //
    QWidget* createPartner();
    int countPartnerItems() const;
    QString getPartnerItem(int _index, const QString& _data) const;
    //
    QWidget* createSocialNetworks();
    int countSocialNetworksItems() const;
    QString getSocialNetworksItem(int _index, const QString& _data) const;

private:

};
//==============================================
#endif
//==============================================
