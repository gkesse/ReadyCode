//===============================================
#ifndef _GQtUi_
#define _GQtUi_
//===============================================
#include "GInclude.h"
//===============================================
class GQtUi : public QWidget {
    Q_OBJECT
    
public:
    GQtUi(QWidget* parent = 0);
    ~GQtUi();
    static GQtUi* Create(const QString& key);
    virtual void resize();
};
//==============================================
#endif
//==============================================
