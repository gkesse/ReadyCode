//===============================================
#ifndef _GProHome_
#define _GProHome_
//===============================================
#include "GProUi.h"
//===============================================
class GProHome : public GProUi {
    Q_OBJECT
    
public:
    GProHome(QWidget* parent = 0);
    ~GProHome();

public slots:
	void slotEvent(const QString& text);
};
//==============================================
#endif
//==============================================
