//===============================================
#ifndef _GStruct_
#define _GStruct_
//===============================================
typedef struct _sGVertex sGVertex;
typedef struct _sGData sGData;
typedef struct _sGColor sGColor;
typedef struct _sGParams sGParams;
typedef struct _sGParams2 sGParams2;
typedef struct _sGParams3 sGParams3;
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
	int cursorX;
	int cursorY;
};
//===============================================
struct _sGParams2 {
	const char* filename;
	int xsize;
	int ysize;
	int zsize;
	int xslice;
	int yslice;
	int zslice;
	float pointsize;
	float linesize;
	float transparency;
	sGColor color;
	float alpha;
	float beta;
	float zoom;
	bool lock;
	int cursorX;
	int cursorY;
};
//===============================================
struct _sGParams3 {
	GLuint vao;
	GLuint vbo_vertex;
	GLuint vbo_color;
	GLuint attrib_vertex;
	GLuint attrib_color;
	const float* vertex;
	const float* color;
	int vertex_size;
	int color_size;
};
//==============================================
#endif
//==============================================
