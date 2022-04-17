//===============================================
#ifndef _GRequestUi_
#define _GRequestUi_
//===============================================
#include "GDialog.h"
//===============================================
class GRequestUi : public GDialog {
	Q_OBJECT

public:
	GRequestUi(QWidget* _parent = 0);
	~GRequestUi();
	void createDoms();
	void createLayout();

public slots:
    void onEvent();
    void onEvent(const QString& _text);
};
//===============================================
#endif
//===============================================
