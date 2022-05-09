//===============================================
#ifndef _GQtSpreadSheet_
#define _GQtSpreadSheet_
//===============================================
#include "GQtTableWidget.h"
//===============================================
class GQtCell;
class GQtSpreadSheetCompare;
//===============================================
class GQtSpreadSheet : public GQtTableWidget {
    Q_OBJECT

public:
    GQtSpreadSheet(QWidget* _parent = 0);
    ~GQtSpreadSheet();
    void clear();
    QString currentLocation() const;
    QString currentFormula() const;
    bool writeFile(const QString& _filename);
    bool readFile(const QString& _filename);
    void cut();
    void copy();
    void paste();
    void del();
    QTableWidgetSelectionRange selectedRange() const;
    void selectCurrentRow();
    void selectCurrentColumn();
    QString text(int row, int column) const;
    QString formula(int row, int column) const;
    void setFormula(int row, int column, const QString &formula);
    GQtCell* cell(int _row, int _column) const;
    void recalculate();
    bool getAutoRecalculate();
    void sort(const GQtSpreadSheetCompare& compare);

public slots:
    void setAutoRecalculate(bool _recalc);
    void somethingChanged(QTableWidgetItem* _item = 0);
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);

signals:
    void modified();

private:
    static const quint32 MagicNumber = 0x7F51C883;
    static const quint16 RowCount = 999;
    static const quint16 ColumnCount = 26;

private:
    bool autoRecalc;
};
//==============================================
class GQtSpreadSheetCompare {
public:
    bool operator()(const QStringList &row1, const QStringList &row2) const;

public:
    static const int KeyCount = 3;

public:
    int keys[KeyCount];
    bool ascending[KeyCount];
};
//==============================================
#endif
//==============================================
