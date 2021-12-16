//===============================================
#ifndef _GQtStudio_
#define _GQtStudio_
//===============================================
#include "GQtMainWindow.h"
//===============================================
class GQtXml;
//===============================================
class GQtStudio : public GQtMainWindow {
    Q_OBJECT

public:
    GQtStudio(QWidget* _parent = 0);
    ~GQtStudio();
    void createDoms();
    void createActions();
    int countMenus() const;
    int countSubMenus(int _menu) const;
    QString getMenuName(int _index) const;
    QString getSubMenuName(int _menu, int _submenu) const;
    QString getSubMenuIcon(int _menu, int _submenu) const;
    QString getTitle() const;
    int getWidth() const;
    int getHeight() const;

public slots:
    void onMenuAction();

private:
    QSharedPointer<GQtXml> m_dom;
};
//==============================================
#endif
//==============================================
