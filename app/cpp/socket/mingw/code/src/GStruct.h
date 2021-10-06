//===============================================
#ifndef _GStruct_
#define _GStruct_
//===============================================
typedef struct _sGVertex sGVertex;
typedef struct _sGData sGData;
typedef struct _sGColor sGColor;
typedef struct _sGParams sGParams;
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
//===============================================
struct _sGParams {
	bool freeze;
	float sigma;
	float sign;
	float step;
	float alpha;
	float beta;
	float zoom;
	bool lock;
};
//==============================================
#endif
//==============================================
