//===============================================
#ifndef _GPadMdi_
#define _GPadMdi_
//===============================================
#include "GMainWindow.h"
//===============================================
class GPadMdi : public GMainWindow {
	Q_OBJECT

public:
	GPadMdi(QWidget* _parent = 0);
	~GPadMdi();
    void createLayout();

public slots:
    void onTriggered(bool _checked = false);
    void onSubWindowActivated(QMdiSubWindow* _window);

private:
    QMdiArea* m_mdiArea;
};
//===============================================
#endif
//===============================================
