//===============================================
#include "GGml.h"
//===============================================
GGml::GGml() {

}
//===============================================
GGml::~GGml() {

}
//===============================================
void GGml::identity() {
	m_mat4 = glm::mat4(1.f);
}
//===============================================
void GGml::rotate(float _angle, float _x, float _y, float _z) {
	m_mat4 = glm::rotate(m_mat4, glm::radians(_angle), glm::vec3(_x, _y, _z));
}
//===============================================
void GGml::lookAt(float _eyeX, float _eyeY, float _eyeZ, float _centerX, float _centerY, float _centerZ, float _upX, float _upY, float _upZ) {
    m_mat4 = glm::lookAt(glm::vec3(_eyeX, _eyeY, _eyeZ), glm::vec3(_centerX, _centerY, _centerZ), glm::vec3(_upX, _upY, _upZ));
}
//===============================================
glm::vec4 GGml::dot(float _x, float _y, float _z, float _w) {
    return m_mat4 * glm::vec4(_x, _y, _z, _w);
}
//===============================================
void GGml::dot(const GGml& _matA, const GGml& _matB) {
    m_mat4 = _matA.mat4() * _matB.mat4();
}
//===============================================
glm::mat4 GGml::mat4() const {
	return m_mat4;
}
//===============================================
glm::mat3 GGml::mat3() const {
	return glm::mat3(glm::vec3(m_mat4[0]), glm::vec3(m_mat4[1]), glm::vec3(m_mat4[2]));
}
//===============================================
