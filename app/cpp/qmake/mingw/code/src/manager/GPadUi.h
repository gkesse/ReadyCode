//===============================================
#ifndef _GPad_
#define _GPad_
//===============================================
#include "GWidget.h"
//===============================================
class GPadUi : public GWidget {
	Q_OBJECT

public:
	GPadUi(QWidget* _parent = 0);
	~GPadUi();
	void createDoms();
    void createLayout();

public slots:
	void onEvent();
	void onEvent(const QString& _text);

protected:
	bool eventFilter(QObject* _obj, QEvent* _event);
};
//===============================================
#endif
//===============================================
