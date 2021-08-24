//===============================================
#ifndef _GAnalogClock_
#define _GAnalogClock_
//===============================================
#include "GQtUi.h"
//===============================================
class GAnalogClock : public GQtUi {
    Q_OBJECT
    
public:
    GAnalogClock(QWidget* parent = 0);
    virtual ~GAnalogClock();
    void resize();

protected:
    void paintEvent(QPaintEvent* event);

public slots:
	void onEvent();
};
//==============================================
#endif
//==============================================
