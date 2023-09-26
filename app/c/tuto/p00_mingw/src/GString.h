//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GString GString;
//===============================================
struct _GString {
    void (*delete)(GString** _this);
    void (*clear)(GString* _this);
    void (*allocate)(GString* _this, int _size);
    void (*create)(GString* _this, const char* _data);
    void (*assign)(GString* _this, GString* _data);
    void (*add)(GString* _this, const char* _data);
    void (*format)(GString* _this, const char* _format, ...);
    void (*split)(GString* _this, GVector* _map, const char* _sep);
    int (*isEmpty)(GString* _this);
    int (*startsWith)(GString* _this, const char* _data);
    int (*endsWith)(GString* _this, const char* _data);
    int (*indexOf)(GString* _this, const char* _data);
    void (*substr)(GString* _this, GString* _data, int _pos, int _size);
    void (*print)(GString* _this);

    char* m_data;
    int m_size;
};
//===============================================
void GString_init(GString* _this);
GString* GString_new();
//===============================================
#endif
//===============================================
