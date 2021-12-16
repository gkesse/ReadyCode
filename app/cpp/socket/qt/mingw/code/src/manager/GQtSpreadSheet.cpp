//===============================================
#include "GQtSpreadSheet.h"
#include "GQtCell.h"
#include "GQtFile.h"
#include "GQtLog.h"
//===============================================
GQtSpreadSheet::GQtSpreadSheet(QWidget* _parent) :
QTableWidget(_parent) {
    setItemPrototype(new GQtCell);
    setSelectionMode(ContiguousSelection);
    clear();
    m_autoRecalc = true;
}
//===============================================
GQtSpreadSheet::~GQtSpreadSheet() {

}
//===============================================
void GQtSpreadSheet::clear() {
    GQTLOG->write(GMSG);
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
bool GQtSpreadSheet::saveFile(const QString& _filename) {
    GQTLOG->write(GMSG);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    GQtFile lFile;
    if(!lFile.openFileWR(_filename)) {
        GQTLOG->addError("Erreur la sauvegarde du tableur a échoué");
        return false;
    }
    lFile.writeData(MagicNumber);
    for (int row = 0; row < RowCount; ++row) {
        for (int column = 0; column < ColumnCount; ++column) {
            QString lFormula = getFormula(row, column);
            if (!lFormula.isEmpty()) {
                lFile.writeData(row).writeData(column).writeData(lFormula);
            }
        }
    }
    QApplication::restoreOverrideCursor();
    return true;
}
//===============================================
bool GQtSpreadSheet::loadFile(const QString& _filename) {
    GQTLOG->write(GMSG);
    GQtFile lFile;
    if(!lFile.openFileRD(_filename)) {
        GQTLOG->addError("Erreur le chargement du tableur a échoué");
        return false;
    }
    int lMagicNumber;
    lFile.getData(lMagicNumber);
    if(lMagicNumber != MagicNumber) {
        GQTLOG->addError(QString("Erreur le fichier n'est pas un tableur : %1").arg(_filename));
        return false;
    }
    clear();
    QApplication::setOverrideCursor(Qt::WaitCursor);
    int lRow, lCol; QString lFormula;
    while(!lFile.atEnd()) {
        lFile.getData(lRow).getData(lCol).getData(lFormula);
        setFormula(lRow, lCol, lFormula);
    }
    QApplication::restoreOverrideCursor();
    return true;
}
//===============================================
QString GQtSpreadSheet::getFormula(int _row, int _column) const {
    GQtCell* lCell = getCell(_row, _column);
    if (lCell) {
        return lCell->getFormula();
    }
    else {
        return "";
    }
}
//===============================================
void GQtSpreadSheet::setFormula(int _row, int _column, const QString& _formula) {
    GQtCell* lCell = getCell(_row, _column);
    if (!lCell) {
        lCell = new GQtCell;
        setItem(_row, _column, lCell);
    }
    lCell->setFormula(_formula);
}
//===============================================
GQtCell* GQtSpreadSheet::getCell(int _row, int _column) const {
    return static_cast<GQtCell*>(item(_row, _column));
}
//===============================================
void GQtSpreadSheet::recalculate() {

}
//===============================================
void GQtSpreadSheet::setAutoRecalculate(bool _recalc) {
    m_autoRecalc = _recalc;
    if (m_autoRecalc) {
        recalculate();
    }
}
//===============================================
bool GQtSpreadSheet::getAutoRecalculate() {
    return m_autoRecalc;
}
//===============================================
