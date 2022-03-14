//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
//===============================================
class GXml;
//===============================================
class GObject : public QObject {
	Q_OBJECT

public:
	GObject(QObject* _parent = 0);
	virtual ~GObject();
	virtual QString getItem(const QString& _key, const QString& _data) const;

protected:
	QSharedPointer<GXml> m_dom;
};
//===============================================
#endif
//===============================================
