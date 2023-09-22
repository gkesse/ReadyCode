//===============================================
#ifndef _GInclude_
#define _GInclude_
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//===============================================
#define GDEFINE_OBJ(_type, _obj) \
    _type _obj; \
    _type##_init(&_obj);
//===============================================
#define GDEFINE_OBJ_PTR(_type, _obj) \
    _type* _obj = _type##_new();
//===============================================
#endif
//===============================================
