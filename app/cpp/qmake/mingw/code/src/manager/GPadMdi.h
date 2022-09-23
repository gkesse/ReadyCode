//===============================================
#ifndef _GPadMdi_
#define _GPadMdi_
//===============================================
#include "GMainWindow.h"
//===============================================
class GConnection;
class GTitleBarApp;
//===============================================
class GPadMdi : public GMainWindow {
	Q_OBJECT

public:
	GPadMdi(QWidget* _parent = 0);
	~GPadMdi();
    void createLayout();
    //
    void onRunConnection();
    void onAccount();
    void onCv();
    void onPocoClientTcp();
    //
    GConnection* getConnection() const;

public slots:
    void onEvent(QAction* _action);
    void onEvent(QMdiSubWindow* _window);

private:
    QMdiArea* m_mdiArea;
    GTitleBarApp* m_titleBar;
    GConnection* m_connection;
};
//===============================================
#endif
//===============================================
