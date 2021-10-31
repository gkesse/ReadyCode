//===============================================
#ifndef _GStruct_
#define _GStruct_
//===============================================
#include "GGml.h"
//===============================================
typedef struct _sGVertex sGVertex;
typedef struct _sGData sGData;
typedef struct _sGData2 sGData2;
typedef struct _sGColor sGColor;
typedef struct _sGCamera sGCamera;
typedef struct _sGMvp sGMvp;
typedef struct _sGMvp2 sGMvp2;
typedef struct _sGNoise sGNoise;
typedef struct _sGLight sGLight;
typedef struct _sGOpenGL sGOpenGL;
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
    GLfloat speedFactor;
};
//==============================================
struct _sGMvp {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};
//==============================================
struct _sGMvp2 {
    GGml model;
    GGml view;
    GGml projection;
    GGml mv;
    GGml mvp;
};
//==============================================
struct _sGNoise {
    float baseFreq;
    float persistence;
    int width;
    int height;
	bool periodic;
};
//==============================================
struct _sGLight {
    GGml world;
};
//===============================================
struct _sGOpenGL {
	sGColor bgcolor;
	sGMvp _mvp;
	sGMvp2 mvp2;
	GLuint vao[1];
	GLuint vbo[3];
	glm::mat4 slice;
	sGNoise noise;
	const char* shader_vertex_code;
	const char* shader_fragment_code;
	GLfloat angle;
	glm::mat4 rotation;
	bool animate;
	sGLight light;
};
//==============================================
#endif
//==============================================
