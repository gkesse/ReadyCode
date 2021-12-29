//===============================================
#ifndef _GQtStudio_
#define _GQtStudio_
//===============================================
#include "GQtMainWindow.h"
//===============================================
class GQtXml;
class GQtSdi;
//===============================================
class GQtStudio : public GQtMainWindow {
    Q_OBJECT

public:
    GQtStudio(QWidget* _parent = 0);
    ~GQtStudio();
    void createDoms();
    void createWindows();

public slots:
    void onMenuAction();

private:
};
//==============================================
#endif
//==============================================
