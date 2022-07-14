//===============================================
#ifndef _GWidget_
#define _GWidget_
//===============================================
#include "GInclude.h"
//===============================================
class GCode;
class GError;
//===============================================
class GWidget : public QFrame {
	Q_OBJECT

public:
	GWidget(QWidget* _parent = 0);
	virtual ~GWidget();
    //
    virtual void createDoms();
    virtual QString getItem(const QString& _code, const QString& _key, bool _isCData = false) const;
    virtual QString getItem(const QString& _code, int _index, bool _isCData = false) const;
    virtual QString getItem(const QString& _code, const QString& _key, int _index, bool _isCData = false) const;
    virtual QString getItem(const QString& _code, const QString& _category, const QString& _key, bool _isCData = false) const;
    virtual int countItem(const QString& _code) const;
    //
    virtual void addObj(const QString& _key, void* _obj);
    virtual void* getObj(const QString& _key, void* _defaultValue = 0) const;
    virtual QString getKey(void* _obj, const QString& _defaultValue = "") const;
    //
    void onErrorKey(const QString& _key);

protected:
    QMap<QString, void*> m_objs;
	QSharedPointer<GCode> m_dom;
    QSharedPointer<GError> m_errors;
};
//===============================================
#endif
//===============================================
