//===============================================
#ifndef _GPadMdiUi_
#define _GPadMdiUi_
//===============================================
#include "GWidget.h"
//===============================================
class GPadMdiUi : public GWidget {
	Q_OBJECT

public:
	GPadMdiUi(QWidget* _parent = 0);
	~GPadMdiUi();
    void createLayout();

protected:
    void resizeEvent(QResizeEvent* event);

private:
    QSizeGrip* m_sizeGrip;
};
//===============================================
#endif
//===============================================
