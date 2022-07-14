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
    //
    void onConnection();
    void onCv();

public slots:
    void onEvent(QAction* _action);
    void onEvent(QMdiSubWindow* _window);

private:
    QMdiArea* m_mdiArea;
};
//===============================================
#endif
//===============================================
