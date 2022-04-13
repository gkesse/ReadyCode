//===============================================
#ifndef _GLogin_
#define _GLogin_
//===============================================
#include "GDialog.h"
//===============================================
class GLoginUi : public GDialog {
	Q_OBJECT

public:
	GLoginUi(QWidget* _parent = 0);
	~GLoginUi();
	void createDoms();
	void createLayout();

public slots:
    void onEvent();
    void onEvent(const QString& _text);
};
//===============================================
#endif
//===============================================
