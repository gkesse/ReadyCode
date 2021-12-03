//===============================================
#ifndef _GQtSpreadSheet_
#define _GQtSpreadSheet_
//===============================================
#include "GInclude.h"
//===============================================
class GQtCell;
//===============================================
class GQtSpreadSheet : public QTableWidget {
    Q_OBJECT

public:
    GQtSpreadSheet(QWidget* _parent = 0);
    ~GQtSpreadSheet();
    void clear();
    bool saveFile(const QString& _filename);
    bool loadFile(const QString& _filename);
    QString getFormula(int _row, int _column) const;
    void setFormula(int _row, int _column, const QString& _formula);
    GQtCell* getCell(int _row, int _column) const;
    void recalculate();
    bool getAutoRecalculate();

public slots:
    void setAutoRecalculate(bool _recalc);

private:
    static const int MagicNumber = 0x7F51C883;
    static const int RowCount = 999;
    static const int ColumnCount = 26;
    bool m_autoRecalc;
};
//==============================================
#endif
//==============================================
