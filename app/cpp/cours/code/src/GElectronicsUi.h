//===============================================
#ifndef _GElectronicsUi_
#define _GElectronicsUi_
//===============================================
#include "GInclude.h"
//===============================================
class GElectronicsUi : public QFrame {
    Q_OBJECT
    
public:
    GElectronicsUi(QWidget* parent = 0);
    virtual ~GElectronicsUi();
    static GElectronicsUi* Create(const QString& key);

public slots:
    virtual void onEvent();
	virtual void onEvent(const QString& text);
	virtual void onEvent(const QPoint& pos);
	virtual void onEvent(int row, int col);
};
//==============================================
#endif
//==============================================
