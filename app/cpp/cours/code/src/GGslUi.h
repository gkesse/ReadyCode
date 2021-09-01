//===============================================
#ifndef _GGslUi_
#define _GGslUi_
//===============================================
#include "GInclude.h"
//===============================================
class GGslUi : public QFrame {
    Q_OBJECT
    
public:
    GGslUi(QWidget* parent = 0);
    virtual ~GGslUi();
    static GGslUi* Create(const QString& key);
    virtual void resize();

public slots:
    virtual void onEvent();
    virtual void onEvent(const QString& text);
    virtual void onEvent(const QPoint& pos);
    virtual void onEvent(int row, int col);
};
//==============================================
#endif
//==============================================
