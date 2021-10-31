//===============================================
#ifndef _GGml_
#define _GGml_
//===============================================
#include "GInclude.h"
//===============================================
class GGml {
public:
    GGml();
    ~GGml();
    void identity();
    void data(float _x, float _y, float _z, float _w);
    void rotate(float _angle, float _x, float _y, float _z);
    void scale(float _x, float _y, float _z);
    void translate(float _x, float _y, float _z);
    void lookAt(float _eyeX, float _eyeY, float _eyeZ, float _centerX, float _centerY, float _centerZ, float _upX, float _upY, float _upZ);
    glm::vec4 dot(float _x, float _y, float _z, float _w);
    glm::vec4 dot(const GGml& _vec4);
    glm::mat4 dot2(const GGml& _mat4);
    void dot(const GGml& _matA, const GGml& _matB);
    glm::mat4 mat4() const;
    glm::mat3 mat3() const;
    void perspective(float _angle, float _zNear, float _zFar, int _width, int _height);

private:
    glm::mat4 m_mat4;
    glm::vec4 m_vec4;
};
//==============================================
#endif
//==============================================
