//===============================================
#ifndef _GStruct_
#define _GStruct_
//===============================================
typedef struct _sGVertex sGVertex;
typedef struct _sGData sGData;
typedef struct _sGColor sGColor;
//==============================================
struct _sGVertex {
    float x, y, z;
    float r, g, b, a;
};
//==============================================
struct _sGData {
    float x, y, z;
};
//==============================================
struct _sGColor {
    float r, g, b, a;
};
//==============================================
#endif
//==============================================
