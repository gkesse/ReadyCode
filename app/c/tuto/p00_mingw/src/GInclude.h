//===============================================
#ifndef _GInclude_
#define _GInclude_
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//===============================================
#define GDEFINE_OBJ(_type, _this) \
    _type _this; \
    _type##_init(&_this);
//===============================================
#define GDEFINE_OBJ_PTR(_type, _this) \
    _type* _this = _type##_new();
//===============================================
#endif
//===============================================
