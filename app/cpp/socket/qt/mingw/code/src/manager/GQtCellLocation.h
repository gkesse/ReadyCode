//===============================================
#ifndef _GQtCellLocation_
#define _GQtCellLocation_
//===============================================
#include "GInclude.h"
//===============================================
class GQtCellLocation : public QDialog {
    Q_OBJECT

public:
    GQtCellLocation(QWidget* _parent = 0);
    ~GQtCellLocation();

public slots:
    void onCellEdit(const QString& _text);

private:
    QLineEdit* m_cellEdit;
    QDialogButtonBox* m_buttonBox;
};
//==============================================
#endif
//==============================================
