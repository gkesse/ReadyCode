//===============================================
#ifndef _GQt_
#define _GQt_
//===============================================
#include "GInclude.h"
//===============================================
#define GQT GQt::Instance()
//===============================================
class GQt {
public:
    GQt();
    ~GQt();
    static GQt* Instance();
    QTextEdit* createQTextEdit(QWidget* _QWidget = 0);
    GQt& addSpacer(QVBoxLayout* _QVBoxLayout);
    GQt& addSpacer(QHBoxLayout* _QHBoxLayout);
    GQt& addVSpacer(QGridLayout* _QGridLayout, int _row, int _column, int _rowSpan = 1, int _columnSpan = 1, Qt::Alignment _alignment = Qt::Alignment());
    GQt& addHSpacer(QGridLayout* _QGridLayout, int _row, int _column, int _rowSpan = 1, int _columnSpan = 1, Qt::Alignment _alignment = Qt::Alignment());
    GQt& setValidator(QLineEdit* _QLineEdit, QString _pattern, QWidget* _parent = 0);
    GQt& setEnabled(QDialogButtonBox* _QDialogButtonBox, QDialogButtonBox::StandardButton _button, bool _ok);
    QString getKey(int _argc, char** _argv, int _index);
    Qt::CaseSensitivity getCaseSensitivity(QCheckBox* _QCheckBox);
    bool isEmpty(QLineEdit* _QLineEdit);
    bool isEmpty(QTextEdit* _QTextEdit);

private:
    static GQt* m_instance;
};
//==============================================
#endif
//==============================================
