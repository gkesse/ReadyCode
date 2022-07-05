//===============================================
#ifndef _GDialog_
#define _GDialog_
//===============================================
#include "GInclude.h"
//===============================================
class GXml;
class GError;
//===============================================
class GDialog : public QDialog {
    Q_OBJECT

public:
    GDialog(QWidget* _parent = 0);
    virtual ~GDialog();
    virtual void createDoms();
    virtual QString getItem(const QString& _code, const QString& _data) const;
    virtual QString getItem(const QString& _code, const QString& _data, int _i) const;
    virtual int countItem(const QString& _code) const;
    void addObject(QObject* _object, const QString& _key);
    QObject* getObject(const QString& _key);
    QString getObject(QObject* _key, const QString& _defaultValue = "");
    //
    void onErrorKey(const QString& _key);

signals:
    void onEmit(const QString& _text);

protected:
    QSharedPointer<GXml> m_dom;
    QMap<QObject*, QString> m_objectMap;
    QSharedPointer<GError> m_errors;
};
//===============================================
#endif
//===============================================
