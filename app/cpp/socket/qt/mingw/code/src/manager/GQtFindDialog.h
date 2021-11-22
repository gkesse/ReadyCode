//===============================================
#ifndef _GQtFindDialog_
#define _GQtFindDialog_
//===============================================
#include "GQtDialog.h"
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
    QPushButton* m_findButton;
    QLineEdit* m_findEdit;
    QCheckBox* m_caseCheckBox;
    QCheckBox* m_backwardCheckBox;
};
//==============================================
#endif
//==============================================
