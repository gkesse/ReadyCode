//===============================================
#ifndef _GQueryUi_
#define _GQueryUi_
//===============================================
#include "GInclude.h"
//===============================================
class GQuery;
//===============================================
namespace Ui {
    class GQueryUi;
}
//===============================================
class GQueryUi : public QFrame {
    Q_OBJECT

public:
    GQueryUi(QWidget* parent = 0);
    ~GQueryUi();

    void readData();
    void writeData();

public slots:
    void on_btnSendEmissionXml_clicked();
    void on_btnNewEmissionXml_clicked();

private:
    Ui::GQueryUi *ui;
    std::shared_ptr<GQuery> m_query;
};
//==============================================
#endif
//==============================================
