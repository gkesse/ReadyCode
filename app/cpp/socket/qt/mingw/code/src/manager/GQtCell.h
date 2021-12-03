//===============================================
#ifndef _GQtCell_
#define _GQtCell_
//===============================================
#include "GInclude.h"
//===============================================
class GQtCell : public QTableWidgetItem {
public:
    GQtCell();
    ~GQtCell();
    QTableWidgetItem* clone() const;
    QVariant data(int _role) const;
    void setData(int role, const QVariant &value);
    QString getFormula() const;
    void setFormula(const QString& _formula);
    void setDirty();

private:
    QVariant value() const;
    QVariant evalExpression(const QString &str, int &pos) const;
    QVariant evalTerm(const QString &str, int &pos) const;
    QVariant evalFactor(const QString &str, int &pos) const;

private:
    mutable QVariant cachedValue;
    mutable bool cacheIsDirty;
};
//==============================================
#endif
//==============================================
