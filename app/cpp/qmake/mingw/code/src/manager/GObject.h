//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
//===============================================
class GObject : public QObject {
	Q_OBJECT

public:
	GObject(QObject* _parent = 0);
	~GObject();
};
//===============================================
#endif
//===============================================
