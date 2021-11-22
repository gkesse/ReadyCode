//===============================================
#ifndef _GQtMainWindow_
#define _GQtMainWindow_
//===============================================
#include "GInclude.h"
#include "GStruct.h"
//===============================================
class GQtMainWindow : public QMainWindow {
    Q_OBJECT

public:
    GQtMainWindow(QWidget* _parent = 0);
    ~GQtMainWindow();
    static GQtMainWindow* Create(const QString& _key, QWidget* _parent = 0);
};
//==============================================
#endif
//==============================================
