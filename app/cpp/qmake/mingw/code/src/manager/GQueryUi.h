//===============================================
#ifndef _GQueryUi_
#define _GQueryUi_
//===============================================
#include "GInclude.h"
//===============================================
class GQuery;
class GQueryType;
class GSearch;
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
    // xml
    void on_btnSendEmissionXml_clicked();
    void on_btnNewEmissionXml_clicked();
    // type
    void onLoadDefaultComboBox();
    void on_btnSaveCreateType_clicked();
    void on_btnSearchCreateType_clicked();
    void on_btnDeleteCreateType_clicked();
    void on_btnNewCreateType_clicked();
    // emission
    void on_btnSendEmission_clicked();
    void on_btnClearEmission_clicked();
    // reception
    void on_btnCopyReception_clicked();
    // search
    void onLoadSearchConfig();

private:
    Ui::GQueryUi *ui;
    std::shared_ptr<GQuery> m_query;
    std::shared_ptr<GQueryType> m_queryType;
    std::shared_ptr<GSearch> m_searchConfig;

    int m_typeId;
};
//==============================================
#endif
//==============================================
