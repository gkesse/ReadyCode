//===============================================
#ifndef _GQtCellLocation_
#define _GQtCellLocation_
//===============================================
#include "GQtDialog.h"
//===============================================
class GQtCellLocation : public GQtDialog {
    Q_OBJECT

public:
    GQtCellLocation(QWidget* _parent = 0);
    ~GQtCellLocation();
    //
    void createDoms();
    QString getTitle() const;
    int getWidth() const;
    int getHeight() const;
    QString getText() const;

public slots:
    void onCellEdit(const QString& _text);

private:
    QLineEdit* m_cellEdit;
    QDialogButtonBox* m_buttonBox;
};
//==============================================
#endif
//==============================================
