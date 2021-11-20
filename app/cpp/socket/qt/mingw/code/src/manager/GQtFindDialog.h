//===============================================
#ifndef _GQtFindDialog_
#define _GQtFindDialog_
//===============================================
#include "GQtDialog.h"
#include "GQt.h"
//===============================================
class GQtFindDialog : public GQtDialog {
    Q_OBJECT

public:
    GQtFindDialog(QWidget* _parent = 0);
    ~GQtFindDialog();

public slots:
    void onFindButton();
    void onFindEdit(const QString& _text);

signals:
    void emitFindPrevious(const QString& _text, Qt::CaseSensitivity _cs);
    void emitFindNext(const QString& _text, Qt::CaseSensitivity _cs);

private:
    GQt m_findButton;
    GQt m_findEdit;
    GQt m_caseCheckBox;
    GQt m_backwardCheckBox;
};
//==============================================
#endif
//==============================================
