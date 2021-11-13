//===============================================
#ifndef _GStruct_
#define _GStruct_
//===============================================
#include "GInclude.h"
//===============================================
struct sGPoint;
struct sGColor;
struct sGVertex;
struct sGCamera;
struct sGMvp;
struct sGNoise;
struct sGSinus;
struct sGGaussian2D;
struct sGWindow;
struct sGRange;
struct sGGrid;
struct sGOpenGL;
struct sGSocket;
//==============================================
class GSocket;
//==============================================
struct sGPoint {
    float x, y, z;
    sGPoint();
    sGPoint(float _x, float _y);
    sGPoint(float _x, float _y, float _z);
    sGPoint(const sGPoint& _p);
    sGPoint& operator*=(const sGPoint& _p);
    friend sGPoint operator*(const sGPoint& _p1, const sGPoint& _p2);
    sGPoint& operator/=(const sGPoint& _p);
    friend sGPoint operator/(const sGPoint& _p1, const sGPoint& _p2);
};
//==============================================
struct sGColor {
    float r, g, b, a;
    sGColor();
    sGColor(float _r, float _g, float _b);
    sGColor(float _r, float _g, float _b, float _a);
    sGColor(const sGColor& _c);
};
//==============================================
struct sGVertex {
    sGPoint d;
    sGColor c;
    sGVertex();
    sGVertex(const sGPoint& _d, const sGColor& _c);
    sGVertex(const sGVertex& _v);
    sGVertex& operator=(const sGVertex& _v);
};
//==============================================
struct sGCamera {
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
    glm::vec3 front;
    GLfloat speed;
    GLfloat speedFactor;
};
//==============================================
struct sGMvp {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};
//==============================================
struct sGNoise {
    float baseFreq;
    float persistence;
    int width;
    int height;
    bool periodic;
};
//==============================================
struct sGSinus {
    float max;
    float phase;
    int size;
    float range;
    float linewidth;
    float pointsize;
    sGColor pointcolor;
    sGColor linecolor;
};
//===============================================
struct sGGaussian2D {
    int xsize;
    int ysize;
    float sigma;
    int size;
    float zmin;
    float zmax;
    float pointsize;
    float alpha;
};
//===============================================
struct sGWindow {
    int width;
    int height;
    std::string title;
    float ratio;
    sGColor bgcolor;
};
//===============================================
struct sGRange {
    float m_min;
    float m_max;
    sGRange();
    sGRange(float _min, float _max);
    sGRange(const sGRange& _r);
    sGRange& operator+=(float _r);
    friend sGRange operator+(const sGRange& _r1, float _r2);
    sGRange& operator-=(float _r);
    friend sGRange operator-(const sGRange& _r1, float _r2);
};
//===============================================
struct sGGrid {
    float width;
    float height;
    float gridWidth;
    float axisWidth;
    float pointsize;
    sGPoint origin;
    sGPoint gridDiv;
    sGPoint axisDiv;
    sGColor gridColor;
    sGColor axisColor;
    sGColor pointColor;
    sGRange xrange;
    sGRange yrange;
    sGRange zrange;
    sGGrid();
};
//===============================================
struct sGOpenGL {
    sGWindow win;
    sGGrid grid;
    sGColor bgcolor;
    sGMvp mvp;
    GLuint vao;
    GLuint vbo[2];
    glm::mat4 slice;
    sGNoise noise;
};
//===============================================
struct sGSocket {
    GSocket* socket;
    std::string address_ip;
    std::string hostname;
    std::string client_ip;
    std::string data;
    int port;
    int backlog;
    int major;
    int minor;
    void* on_start;
    sGSocket();
};
//==============================================
#endif
//==============================================
