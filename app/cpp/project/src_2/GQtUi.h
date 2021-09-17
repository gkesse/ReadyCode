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

public slots:
    virtual void onEvent();
	virtual void onEvent(const QString& text);
	virtual void onEvent(const QPoint& pos);
	virtual void onEvent(int row, int col);
};
//==============================================
#endif
//==============================================
