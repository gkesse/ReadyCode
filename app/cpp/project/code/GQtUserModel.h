//===============================================
#ifndef _GQtUserModel_
#define _GQtUserModel_
//===============================================
#include "GInclude.h"
//===============================================
class GQtUserModel : public QAbstractItemModel {
    Q_OBJECT
    
public:
    GQtUserModel(QObject* parent = 0);
    ~GQtUserModel();

protected:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
};
//==============================================
#endif
//==============================================
