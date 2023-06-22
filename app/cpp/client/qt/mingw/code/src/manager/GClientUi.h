//===============================================
#ifndef _GClientUi_
#define _GClientUi_
//===============================================
#include "GMainWindow.h"
//===============================================
namespace Ui {
class GClientUi;
}
//===============================================
class GClientUi : public GMainWindow {
    Q_OBJECT

public:
    GClientUi(QWidget* _parent = 0);
    ~GClientUi();

protected:
    void closeEvent(QCloseEvent* _event);

public slots:
    void on_actionFacade_triggered(bool _checked = false);
    void on_actionCalculator_triggered(bool _checked = false);

private:
    Ui::GClientUi* ui;
    GString m_facade;
};
//===============================================
#endif
//===============================================
