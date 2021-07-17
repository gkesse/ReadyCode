//===============================================
#include "GQtUserModel.h"
//===============================================
GQtUserModel::GQtUserModel(QObject* parent) : 
QAbstractItemModel(parent) {

}
//===============================================
GQtUserModel::~GQtUserModel() {

}
//===============================================
QModelIndex GQtUserModel::index(int row, int column, const QModelIndex &parent) const {
    return QModelIndex();
}
//===============================================
QModelIndex GQtUserModel::parent(const QModelIndex &index) const {
    return QModelIndex();    
}
//===============================================
int GQtUserModel::rowCount(const QModelIndex &parent) const {
    return 5;
}
//===============================================
int GQtUserModel::columnCount(const QModelIndex &parent) const {
    return 5;
}
//===============================================
QVariant GQtUserModel::data(const QModelIndex &index, int role) const {
    return QVariant();
}
//===============================================
