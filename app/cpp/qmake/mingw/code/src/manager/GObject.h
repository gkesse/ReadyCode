//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
//===============================================
class GCode;
class GError;
//===============================================
class GObject : public QObject {
	Q_OBJECT

public:
    GObject(QObject* _parent = 0);
	virtual ~GObject();
	//
	virtual void createDoms();
    virtual QString getItem(const QString& _code, const QString& _key, bool _isCData = false) const;
    virtual QString getItem(const QString& _code, int _index, bool _isCData = false) const;
    virtual QString getItem(const QString& _code, const QString& _key, int _index, bool _isCData = false) const;
    virtual QString getItem(const QString& _code, const QString& _category, const QString& _key, bool _isCData) const;
    virtual int countItem(const QString& _code) const;
    //
    virtual bool hasErrors() const;
    virtual void clearErrors();
    virtual QVector<QString>& getErrors();
    virtual const QVector<QString>& getErrors() const;
    //
	virtual void runDefault(int _argc, char** _argv);
	//
    virtual void addObj(const QString& _key, void* _obj);
    virtual void* getObj(const QString& _key, void* _defaultValue = 0) const;
    virtual QString getKey(void* _obj, const QString& _defaultValue = "") const;

protected:
    QMap<QString, void*> m_objs;
    QSharedPointer<GCode> m_dom;
    QSharedPointer<GError> m_errors;
};
//===============================================
#endif
//===============================================
