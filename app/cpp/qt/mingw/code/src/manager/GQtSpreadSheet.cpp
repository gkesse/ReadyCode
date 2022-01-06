//===============================================
#include "GQtSpreadSheet.h"

#include "GQtCell.h"
#include "GQtLog.h"
//===============================================
GQtSpreadSheet::GQtSpreadSheet(QWidget* _parent) :
GQtTableWidget(_parent) {
    setItemPrototype(new GQtCell);
    setSelectionMode(ContiguousSelection);
    clear();
    autoRecalc = true;
    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(somethingChanged(QTableWidgetItem*)));
}
//===============================================
GQtSpreadSheet::~GQtSpreadSheet() {

}
//===============================================
void GQtSpreadSheet::clear() {
    setRowCount(0);
    setColumnCount(0);
    setRowCount(RowCount);
    setColumnCount(ColumnCount);

    for (int i = 0; i < ColumnCount; ++i) {
        QTableWidgetItem* lItem = new QTableWidgetItem;
        lItem->setText(QString(QChar('A' + i)));
        setHorizontalHeaderItem(i, lItem);
    }

    setCurrentCell(0, 0);
}
//===============================================
QString GQtSpreadSheet::currentLocation() const {
    return QChar('A' + currentColumn()) + QString::number(currentRow() + 1);
}
//===============================================
QString GQtSpreadSheet::currentFormula() const {
    return text(currentRow(), currentColumn());
}
//===============================================
bool GQtSpreadSheet::writeFile(const QString& _filename) {
    QFile lFile(_filename);
    if (!lFile.open(QIODevice::WriteOnly)) {
        GQTLOG->addError(QString("Erreur la methode (saveFile) a echoue "
                "sur le fichier (%1).\n").arg(_filename));
        return false;
    }

    QDataStream out(&lFile);
    out.setVersion(QDataStream::Qt_5_15);
    out << quint32(MagicNumber);

    QApplication::setOverrideCursor(Qt::WaitCursor);

    for (int row = 0; row < RowCount; ++row) {
        for (int column = 0; column < ColumnCount; ++column) {
            QString lFormula = text(row, column);
            if (!lFormula.isEmpty()) {
                out << quint16(row) << quint16(column) << lFormula;
            }
        }
    }

    QApplication::restoreOverrideCursor();
    return true;
}
//===============================================
bool GQtSpreadSheet::readFile(const QString& _filename) {
    QFile lFile(_filename);
    if (!lFile.open(QIODevice::ReadOnly)) {
        GQTLOG->addError(QString("Erreur la methode (loadFile) a echoue "
                "sur le fichier (%1) (1).\n").arg(_filename));
        return false;
    }

    QDataStream in(&lFile);
    in.setVersion(QDataStream::Qt_5_15);

    quint32 lMagicNumber;
    in >> lMagicNumber;
    if (lMagicNumber != MagicNumber) {
        GQTLOG->addError(QString("Erreur la methode (loadFile) a echoue "
                "sur le fichier (%1) (2).\n").arg(_filename));
        return false;
    }

    clear();

    QApplication::setOverrideCursor(Qt::WaitCursor);

    int lRow, lCol; QString lFormula;
    while(!in.atEnd()) {
        in >> lRow >> lCol >> lFormula;
        setFormula(lRow, lCol, lFormula);
    }

    QApplication::restoreOverrideCursor();
    return true;
}
//===============================================
void GQtSpreadSheet::cut() {
    copy();
    del();
}
//===============================================
void GQtSpreadSheet::copy() {
    QTableWidgetSelectionRange range = selectedRange();
    QString str;

    for (int i = 0; i < range.rowCount(); ++i) {
        if (i > 0)
            str += "\n";
        for (int j = 0; j < range.columnCount(); ++j) {
            if (j > 0)
                str += "\t";
            str += text(range.topRow() + i, range.leftColumn() + j);
        }
    }
    QApplication::clipboard()->setText(str);
}
//===============================================
void GQtSpreadSheet::paste() {
    QTableWidgetSelectionRange range = selectedRange();
    QString str = QApplication::clipboard()->text();
    QStringList rows = str.split('\n');
    int numRows = rows.count();
    int numColumns = rows.first().count('\t') + 1;

    if (range.rowCount() * range.columnCount() != 1
            && (range.rowCount() != numRows
                || range.columnCount() != numColumns)) {
        QMessageBox::information(this, tr("Spreadsheet"),
                tr("The information cannot be pasted because the copy "
                   "and paste areas aren't the same size."));
        return;
    }

    for (int i = 0; i < numRows; ++i) {
        QStringList columns = rows[i].split('\t');
        for (int j = 0; j < numColumns; ++j) {
            int row = range.topRow() + i;
            int column = range.leftColumn() + j;
            if (row < RowCount && column < ColumnCount)
                setFormula(row, column, columns[j]);
        }
    }
    somethingChanged();
}
//===============================================
void GQtSpreadSheet::del() {
    QList<QTableWidgetItem *> items = selectedItems();
    if (!items.isEmpty()) {
        foreach (QTableWidgetItem *item, items)
            delete item;
        somethingChanged();
    }
}
//===============================================
QTableWidgetSelectionRange GQtSpreadSheet::selectedRange() const {
    QList<QTableWidgetSelectionRange> ranges = selectedRanges();
    if (ranges.isEmpty()) {
        return QTableWidgetSelectionRange();
    }
    return ranges.first();
}
//===============================================
void GQtSpreadSheet::selectCurrentRow() {
    selectRow(currentRow());
}
//===============================================
void GQtSpreadSheet::selectCurrentColumn() {
    selectColumn(currentColumn());
}
//===============================================
void GQtSpreadSheet::somethingChanged(QTableWidgetItem* _item) {
    if (autoRecalc) {
        recalculate();
    }
    emit modified();
}
//===============================================
void GQtSpreadSheet::findNext(const QString &str, Qt::CaseSensitivity cs) {
    int row = currentRow();
    int column = currentColumn() + 1;

    while (row < RowCount) {
        while (column < ColumnCount) {
            if (text(row, column).contains(str, cs)) {
                clearSelection();
                setCurrentCell(row, column);
                activateWindow();
                return;
            }
            ++column;
        }
        column = 0;
        ++row;
    }
    QApplication::beep();
}
//===============================================
void GQtSpreadSheet::findPrevious(const QString &str, Qt::CaseSensitivity cs) {
    int row = currentRow();
    int column = currentColumn() - 1;

    while (row >= 0) {
        while (column >= 0) {
            if (text(row, column).contains(str, cs)) {
                clearSelection();
                setCurrentCell(row, column);
                activateWindow();
                return;
            }
            --column;
        }
        column = ColumnCount - 1;
        --row;
    }
    QApplication::beep();
}
//===============================================
QString GQtSpreadSheet::text(int row, int column) const {
    GQtCell *c = cell(row, column);
    if (c) {
        return c->text();
    }
    else {
        return "";
    }
}
//===============================================
QString GQtSpreadSheet::formula(int row, int column) const {
    GQtCell *c = cell(row, column);
    if (c) {
        return c->formula();
    }
    else {
        return "";
    }
}
//===============================================
void GQtSpreadSheet::setFormula(int row, int column, const QString &formula) {
    GQtCell *c = cell(row, column);
    if (!c) {
        c = new GQtCell;
        setItem(row, column, c);
    }
    c->setFormula(formula);
}
//===============================================
GQtCell* GQtSpreadSheet::cell(int _row, int _column) const {
    return static_cast<GQtCell*>(item(_row, _column));
}
//===============================================
void GQtSpreadSheet::recalculate() {
    for (int row = 0; row < RowCount; ++row) {
        for (int column = 0; column < ColumnCount; ++column) {
            if (cell(row, column)) {
                cell(row, column)->setDirty();
            }
        }
    }
    viewport()->update();
}
//===============================================
void GQtSpreadSheet::setAutoRecalculate(bool _recalc) {
    autoRecalc = _recalc;
    if (autoRecalc) {
        recalculate();
    }
}
//===============================================
bool GQtSpreadSheet::getAutoRecalculate() {
    return autoRecalc;
}
//===============================================
void GQtSpreadSheet::sort(const GQtSpreadSheetCompare& compare) {
    QList<QStringList> rows;
    QTableWidgetSelectionRange range = selectedRange();
    int i;

    for (i = 0; i < range.rowCount(); ++i) {
        QStringList row;
        for (int j = 0; j < range.columnCount(); ++j) {
            row.append(text(range.topRow() + i, range.leftColumn() + j));
        }
        rows.append(row);
    }

    //qStableSort(rows.begin(), rows.end(), compare);

    for (i = 0; i < range.rowCount(); ++i) {
        for (int j = 0; j < range.columnCount(); ++j) {
            setFormula(range.topRow() + i, range.leftColumn() + j, rows[i][j]);
        }
    }

    clearSelection();
    somethingChanged();
}
//===============================================
bool GQtSpreadSheetCompare::operator()(const QStringList &row1, const QStringList &row2) const {
    for (int i = 0; i < KeyCount; ++i) {
        int column = keys[i];
        if (column != -1) {
            if (row1[column] != row2[column]) {
                if (ascending[i]) {
                    return row1[column] < row2[column];
                }
                else {
                    return row1[column] > row2[column];
                }
            }
        }
    }
    return false;
}
//===============================================
