//===============================================
#ifndef _GClient_
#define _GClient_
//===============================================
#include "GMainWindow.h"
//===============================================
namespace Ui {
class GClient;
}
//===============================================
class GClient : public GMainWindow {
    Q_OBJECT

public:
    GClient(QWidget* _parent = 0);
    ~GClient();

protected:
    void closeEvent(QCloseEvent* _event);

public slots:
    void on_actionCalculator_triggered(bool _checked = false);

private:
    Ui::GClient* ui;
};
//===============================================
#endif
//===============================================
