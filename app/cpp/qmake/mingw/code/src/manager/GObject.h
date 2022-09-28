//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GCode;
//===============================================
class GObject : public QObject {
public:
    GObject();
	virtual ~GObject();
    virtual GObject* clone();
    virtual QString serialize(const QString& _code = "object");
    virtual void deserialize(const QString& _data, const QString& _code = "object");
    virtual bool clearMap(QVector<GObject*>& _map);
    virtual void setIsParent(bool _isParent);
	//
	virtual void createDoms();
    virtual QString getItem(const QString& _code, const QString& _key) const;
    virtual QString getItem(const QString& _code, int _index) const;
    virtual QString getItem(const QString& _code, const QString& _key, int _index) const;
    virtual QString getItem(const QString& _code, const QString& _category, const QString& _key) const;
    virtual int countItem(const QString& _code) const;
    //
	virtual void runDefault(int _argc, char** _argv);
	//
    virtual void addObj(const QString& _key, void* _obj);
    virtual void* getObj(const QString& _key, void* _defaultValue = 0) const;
    virtual QString getKey(void* _obj, const QString& _defaultValue = "") const;

protected:
    QMap<QString, void*> m_objs;
    QSharedPointer<GCode> m_dom;
    bool m_isParent;
};
//===============================================
#endif
//===============================================
