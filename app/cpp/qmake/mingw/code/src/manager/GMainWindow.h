//===============================================
#ifndef _GMainWindow_
#define _GMainWindow_
//===============================================
#include "GInclude.h"
//===============================================
class GCode;
class GUser;
//===============================================
class GMainWindow : public QMainWindow {
	Q_OBJECT

public:
	GMainWindow(QWidget* _parent = 0);
	virtual ~GMainWindow();
    //
    virtual void createDoms();
    virtual QString getItem(const QString& _code, const QString& _key) const;
    virtual QString getItem(const QString& _code, int _index) const;
    virtual QString getItem(const QString& _code, const QString& _key, int _index) const;
    virtual QString getItem(const QString& _code, const QString& _category, const QString& _key) const;
    virtual int countItem(const QString& _code) const;
    //
    virtual void addObj(const QString& _key, void* _obj);
    virtual void* getObj(const QString& _key, void* _defaultValue = 0) const;
    virtual QString getKey(void* _obj, const QString& _defaultValue = "") const;
    //
    virtual void onErrorKey(const QString& _key);

protected:
    QMap<QString, void*> m_objs;
	QSharedPointer<GCode> m_dom;
};
//===============================================
#endif
//===============================================
