//===============================================
#include "GQtTableWidgetItem.h"
#include "GQtCell.h"
//===============================================
GQtTableWidgetItem::GQtTableWidgetItem() {

}
//===============================================
GQtTableWidgetItem::~GQtTableWidgetItem() {

}
//===============================================
GQtTableWidgetItem* GQtTableWidgetItem::Create(const QString& _key) {
    if(_key == "default") return new GQtTableWidgetItem;
    if(_key == "item/cell") return new GQtCell;
    return new GQtTableWidgetItem;
}
//===============================================
void GQtTableWidgetItem::setFormula(const QString& _formula) {}
QString GQtTableWidgetItem::getFormula() const {return "";}
//===============================================


