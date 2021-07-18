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
    virtual ~GQtUi();
    static GQtUi* Create(const QString& key);
    virtual void onEvent(const QString& event);

public slots:
    virtual void slotEvent();
	virtual void slotEvent(const QPoint& pos);
	virtual void slotEvent(int row, int col);
};
//==============================================
#endif
//==============================================
