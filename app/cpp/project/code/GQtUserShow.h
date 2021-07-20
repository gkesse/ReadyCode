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

public slots:
	void onEvent(const QString& text);
	void onEvent(const QPoint& pos);
	void onEvent(int row, int col);
};
//==============================================
#endif
//==============================================
