//===============================================
#ifndef _GQtUserShow_
#define _GQtUserShow_
//===============================================
#include "GQtUi.h"
//===============================================
class GQtUserShow : public GQtUi {
    Q_OBJECT
    
public:
    GQtUserShow(QWidget* parent = 0);
    ~GQtUserShow();
    void onEvent(const QString& event);

public slots:
	void slotEvent(const QPoint& pos);
	void slotEvent(int row, int col);
};
//==============================================
#endif
//==============================================
