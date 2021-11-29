//===============================================
#include "GQtTableWidget.h"
#include "GQtSpreadSheet.h"
//===============================================
GQtTableWidget::GQtTableWidget(QWidget* _parent) :
QTableWidget(_parent) {

}
//===============================================
GQtTableWidget::~GQtTableWidget() {

}
//===============================================
GQtTableWidget* GQtTableWidget::Create(const QString& _key, QWidget* _parent) {
    if(_key == "default") return new GQtTableWidget(_parent);
    if(_key == "page/spreadsheet") return new GQtSpreadSheet(_parent);
    return new GQtTableWidget(_parent);
}
//===============================================
bool GQtTableWidget::saveFile(const QString &fileName) {return true;}
bool GQtTableWidget::loadFile(const QString &fileName) {return true;}
void GQtTableWidget::setAutoRecalculate(bool _recalc) {}
bool GQtTableWidget::getAutoRecalculate() {return true;}
//===============================================

