//===============================================
#include "GQtSpreadSheet.h"
#include "GQtTableWidgetItem.h"
#include "GQtFile.h"
#include "GQt.h"
#include "GLog.h"
//===============================================
GQtSpreadSheet::GQtSpreadSheet(QWidget* _parent) :
GQtTableWidget(_parent) {
    setItemPrototype(GQtTableWidgetItem::Create("item/cell"));
    setSelectionMode(ContiguousSelection);
    clear();
    m_autoRecalc = true;
}
//===============================================
GQtSpreadSheet::~GQtSpreadSheet() {

}
//===============================================
void GQtSpreadSheet::clear() {
    GLOG->showMsg(GMSG);
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
    GLOG->showMsg(GMSG);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    GQtFile lFile;
    if(!lFile.openFileWR(_filename)) {
        GLOG->addError(GERR, "Erreur la sauvegarde du tableur a échoué");
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
    GLOG->showMsg(GMSG);
    GQtFile lFile;
    if(!lFile.openFileRD(_filename)) {
        GLOG->addError(GERR, "Erreur le chargement du tableur a échoué");
        return false;
    }
    int lMagicNumber;
    lFile.getData(lMagicNumber);
    if(lMagicNumber != MagicNumber) {
        GLOG->addError(GERR, "Erreur le fichier n'est pas un tableur\n(%s)", _filename.toStdString().c_str());
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
    GQtTableWidgetItem* lCell = getCell(_row, _column);
    if (lCell) {
        return lCell->getFormula();
    }
    else {
        return "";
    }
}
//===============================================
void GQtSpreadSheet::setFormula(int _row, int _column, const QString& _formula) {
    GQtTableWidgetItem* lCell = getCell(_row, _column);
    if (!lCell) {
        lCell = GQtTableWidgetItem::Create("item/cell");
        setItem(_row, _column, lCell);
    }
    lCell->setFormula(_formula);
}
//===============================================
GQtTableWidgetItem* GQtSpreadSheet::getCell(int _row, int _column) const {
    return static_cast<GQtTableWidgetItem*>(item(_row, _column));
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
