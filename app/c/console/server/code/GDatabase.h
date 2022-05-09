//===============================================
#ifndef _GDatabase_
#define _GDatabase_
//===============================================
#include <stdio.h>
#include <stdlib.h>
//===============================================
typedef struct _GDatabaseO GDatabaseO;
//===============================================
struct _GDatabaseO {
    void (*Delete)();
    void (*Open)();
    void (*Load)();
    void (*Update)();
    void (*Save)();
};
//===============================================
GDatabaseO* GDatabase();
//===============================================
#endif
//===============================================
