//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GString GString;
typedef struct _GVector GVector;
//===============================================
struct _GString {
    char* m_data;
    int m_size;

    void (*delete)(GString* _this);
    void (*clear)(GString* _this);
    void (*allocate)(GString* _this, int _size);
    void (*create)(GString* _this, const char* _data);
    void (*add)(GString* _this, const char* _data);
    void (*format)(GString* _this, const char* _format, ...);
    GVector* (*split)(GString* _this, const char* _data, const char* _sep);
    void (*print)(GString* _this);
};
//===============================================
GString* GString_new();
//===============================================
#endif
//===============================================
