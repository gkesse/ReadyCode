//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
#include "GString.h"
#include "GLog.h"
//===============================================
class GObject {
public:
    GObject();
    ~GObject();
    const GLog& getLogs() const;

protected:
    GLog m_logs;
};
//===============================================
#endif
//===============================================
