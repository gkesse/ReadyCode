//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GString GString;
//===============================================
struct _GString {
    char* m_data;
    int m_size;

    void (*delete)(GString* _this);
    void (*clear)(GString* _this);
    void (*allocate)(GString* _this, int _size);
    void (*setObj)(GString* _this, GString* _obj);
    void (*create)(GString* _this, const char* _data);
    void (*add)(GString* _this, const char* _data);
    void (*format)(GString* _this, const char* _format, ...);
    void (*print)(GString* _this);
};
//===============================================
GString* GString_new();
//===============================================
#endif
//===============================================
