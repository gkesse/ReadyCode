//===============================================
#ifndef _GStruct_
#define _GStruct_
//===============================================
typedef struct _sGVertex sGVertex;
typedef struct _sGData sGData;
typedef struct _sGData2 sGData2;
typedef struct _sGColor sGColor;
typedef struct _sGCamera sGCamera;
typedef struct _sGMvp sGMvp;
typedef struct _sGParams sGParams;
typedef struct _sGParams2 sGParams2;
typedef struct _sGParams3 sGParams3;
typedef struct _sGParams4 sGParams4;
typedef struct _sGParams5 sGParams5;
typedef struct _sGParams6 sGParams6;
typedef struct _sGParams7 sGParams7;
typedef struct _sGParams8 sGParams8;
typedef struct _sGParams9 sGParams9;
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
struct _sGData2 {
    double x, y, z;
};
//==============================================
struct _sGColor {
    float r, g, b, a;
};
//==============================================
struct _sGCamera {
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
    glm::vec3 front;
    GLfloat speed;
};
//==============================================
struct _sGMvp {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
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
//===============================================
struct _sGParams4 {
	sGCamera cam;
	int solid;
	int indice;
	GLuint* indices;
	int normal;
	int ncircle;
	int nvertex;
	float pointsize;
	GLfloat* vertex;
	GLfloat* normals;
	float rho;
	float theta;
	float phi;
};
//===============================================
struct _sGParams5 {
	sGColor color;
	std::string shader_vertex_code;
	std::string shader_fragment_code;
	GLuint vao;
	GLuint vbo;
};
//===============================================
struct _sGParams6 {
	sGColor color;
	std::string vertex_code;
	std::string fragment_code;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
};
//===============================================
struct _sGParams7 {
	sGColor color;
	std::string vertex_code;
	std::string fragment_code;
	GLuint vao[2];
	GLuint vbo[2];
};
//===============================================
struct _sGParams8 {
	sGColor color;
	std::string vertex_code;
	std::string fragment_code;
	std::string fragment_code2;
	GLuint vao[2];
	GLuint vbo[2];
};
//===============================================
struct _sGParams9 {
	sGColor color;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLfloat mixValue;
	sGCamera cam;
	GLfloat radius;
	GLfloat angle;
	sGMvp mvp;
	GLfloat deltaTime;
	GLfloat lastTime;
};
//==============================================
#endif
//==============================================
