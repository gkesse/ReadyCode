//===============================================
#ifndef _GClient_
#define _GClient_
//===============================================
#include "GInclude.h"
//===============================================
namespace Ui {
class GClient;
}
//===============================================
class GClient : public QMainWindow {
    Q_OBJECT

public:
    GClient(QWidget *parent = 0);
    ~GClient();

private:
    Ui::GClient *ui;
};
//===============================================
#endif
//===============================================
