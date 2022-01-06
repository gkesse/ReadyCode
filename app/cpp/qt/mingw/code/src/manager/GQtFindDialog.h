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
    void createDoms();
    QString getTitle() const;
    int getWidth() const;
    int getHeight() const;

public slots:
    void onFindButton();
    void onFindEdit(const QString& _text);

signals:
    void findPrevious(const QString& _text, Qt::CaseSensitivity _cs);
    void findNext(const QString& _text, Qt::CaseSensitivity _cs);

private:
    QPushButton* m_findButton;
    QLineEdit* m_findEdit;
    QCheckBox* m_caseCheckBox;
    QCheckBox* m_backwardCheckBox;
};
//==============================================
#endif
//==============================================
