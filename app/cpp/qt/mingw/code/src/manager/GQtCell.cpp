//===============================================
#include "GQtCell.h"
#include "GQt.h"
#include "GQtLog.h"
//===============================================
GQtCell::GQtCell() {
    cacheIsDirty = false;
}
//===============================================
GQtCell::~GQtCell() {

}
//===============================================
QTableWidgetItem* GQtCell::clone() const {
    return new GQtCell(*this);
}
//===============================================
QVariant GQtCell::data(int _role) const {
    if (_role == Qt::DisplayRole) {
        if (value().isValid()) {
            return value().toString();
        }
        else {
            return "####";
        }
    }
    else if (_role == Qt::TextAlignmentRole) {
        if (value().type() == QVariant::String) {
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        }
        else {
            return int(Qt::AlignRight | Qt::AlignVCenter);
        }
    }
    else {
        return QTableWidgetItem::data(_role);
    }
}
//===============================================
void GQtCell::setData(int _role, const QVariant& _value) {
    QTableWidgetItem::setData(_role, _value);
    if (_role == Qt::EditRole) {
        setDirty();
    }
}
//===============================================
QString GQtCell::getFormula() const {
    return data(Qt::EditRole).toString();
}
//===============================================
void GQtCell::setFormula(const QString& _formula) {
    setData(Qt::EditRole, _formula);
}
//===============================================
QVariant GQtCell::value() const {
    if (cacheIsDirty) {
        cacheIsDirty = false;

        QString lFormulaStr = getFormula();
        if (lFormulaStr.startsWith('\'')) {
            cachedValue = lFormulaStr.mid(1);
        }
        else if (lFormulaStr.startsWith('=')) {
            cachedValue = QVariant();
            QString expr = lFormulaStr.mid(1);
            expr.replace(" ", "");
            expr.append(QChar::Null);

            int pos = 0;
            cachedValue = evalExpression(expr, pos);
            if (expr[pos] != QChar::Null)
                cachedValue = QVariant();
        }
        else {
            bool ok;
            double d = lFormulaStr.toDouble(&ok);
            if (ok) {
                cachedValue = d;
            }
            else {
                cachedValue = lFormulaStr;
            }
        }
    }
    return cachedValue;
}
//===============================================
QVariant GQtCell::evalExpression(const QString &str, int &pos) const {
    QVariant result = evalTerm(str, pos);
    while (str[pos] != QChar::Null) {
        QChar op = str[pos];
        if (op != '+' && op != '-')
            return result;
        ++pos;

        QVariant term = evalTerm(str, pos);
        if (result.type() == QVariant::Double
                && term.type() == QVariant::Double) {
            if (op == '+') {
                result = result.toDouble() + term.toDouble();
            } else {
                result = result.toDouble() - term.toDouble();
            }
        } else {
            result = QVariant();
        }
    }
    return result;
}
//===============================================
QVariant GQtCell::evalTerm(const QString &str, int &pos) const {
    QVariant result = evalFactor(str, pos);
    while (str[pos] != QChar::Null) {
        QChar op = str[pos];
        if (op != '*' && op != '/')
            return result;
        ++pos;

        QVariant factor = evalFactor(str, pos);
        if (result.type() == QVariant::Double
                && factor.type() == QVariant::Double) {
            if (op == '*') {
                result = result.toDouble() * factor.toDouble();
            } else {
                if (factor.toDouble() == 0.0) {
                    result = QVariant();
                } else {
                    result = result.toDouble() / factor.toDouble();
                }
            }
        } else {
            result = QVariant();
        }
    }
    return result;
}
//===============================================
QVariant GQtCell::evalFactor(const QString &str, int &pos) const {
    QVariant result;
    bool negative = false;

    if (str[pos] == '-') {
        negative = true;
        ++pos;
    }

    if (str[pos] == '(') {
        ++pos;
        result = evalExpression(str, pos);
        if (str[pos] != ')')
            result = QVariant();
        ++pos;
    } else {
        QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
        QString token;

        while (str[pos].isLetterOrNumber() || str[pos] == '.') {
            token += str[pos];
            ++pos;
        }

        if (regExp.exactMatch(token)) {
            int column = token[0].toUpper().unicode() - 'A';
            int row = token.mid(1).toInt() - 1;

            GQtCell *c = static_cast<GQtCell*>(tableWidget()->item(row, column));
            if (c) {
                result = c->value();
            } else {
                result = 0.0;
            }
        } else {
            bool ok;
            result = token.toDouble(&ok);
            if (!ok)
                result = QVariant();
        }
    }

    if (negative) {
        if (result.type() == QVariant::Double) {
            result = -result.toDouble();
        } else {
            result = QVariant();
        }
    }
    return result;
}
//===============================================
void GQtCell::setDirty() {
    cacheIsDirty = true;
}
//===============================================
