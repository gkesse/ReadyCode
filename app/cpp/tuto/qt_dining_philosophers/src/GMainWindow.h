//===============================================
#ifndef _GMainWindow_
#define _GMainWindow_
//===============================================
#include "GInclude.h"
//===============================================
class GDinner;
//===============================================
namespace Ui {
class GMainWindow;
}
//===============================================
class GMainWindow : public QMainWindow {
	Q_OBJECT

public:
	GMainWindow(QWidget* _parent = 0);
	~GMainWindow();
	void init();

public slots:
	void on_actionAboutQt_triggered(bool checked = false);
	void on_actionClose_triggered(bool checked = false);
	void on_actionSettings_triggered(bool checked = false);
	void on_actionStart_triggered(bool checked = false);
	void on_actionStop_triggered(bool checked = false);

signals:
	void emitStart();
	void emitStop();

private:
    Ui::GMainWindow* ui;
    GDinner* m_dinner;
};
//===============================================
#endif
//===============================================
