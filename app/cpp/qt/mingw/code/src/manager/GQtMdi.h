//===============================================
#ifndef _GQtMdi_
#define _GQtMdi_
//===============================================
#include "GQtMainWindow.h"
//===============================================
class GQtXml;
class GQtMdiChild;
//===============================================
class GQtMdi : public GQtMainWindow {
    Q_OBJECT

public:
    GQtMdi(QWidget* _parent = 0);
    ~GQtMdi();
    void createDoms();
    void createCentralWidget();
    GQtMdiChild* createMdiChild();
    void writeSettings();
    bool openFile(const QString& fileName);
    QMdiSubWindow* findMdiChild(const QString &fileName) const;
    bool loadFile(const QString &_filename);
    GQtMdiChild* activeMdiChild() const;
    void updateMenus();

public slots:
    void onMenuAction();
    void onMenuBox();
    void onMenuBoxAction();
    void onMdiAreaSubWindow(QMdiSubWindow* _subWindow);

protected:
    void closeEvent(QCloseEvent *event);

private:
    QMdiArea* m_mdiArea;
};
//==============================================
#endif
//==============================================
