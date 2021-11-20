//===============================================
#ifndef _GQtCellLocation_
#define _GQtCellLocation_
//===============================================
#include "GQtDialog.h"
#include "GQt.h"
//===============================================
class GQtCellLocation : public GQtDialog {
    Q_OBJECT

public:
    GQtCellLocation(QWidget* _parent = 0);
    ~GQtCellLocation();

public slots:
    void onOkButton();
    void onCellEdit(const QString& _text);

signals:
    void emitFindPrevious(const QString& _text, Qt::CaseSensitivity _cs);
    void emitFindNext(const QString& _text, Qt::CaseSensitivity _cs);

private:
    GQt m_okButton;
    GQt m_cellEdit;
};
//==============================================
#endif
//==============================================
