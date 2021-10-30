//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
//===============================================
class GObject {
public:
    GObject();
    ~GObject();
    void torus(GLfloat _outerRadius, GLfloat _innerRadius, GLuint _nsides, GLuint _nrings);
    void init();
    void deletes();
    void render() const;

private:
	std::vector<GLfloat> m_points;
	std::vector<GLfloat> m_normals;
	std::vector<GLfloat> m_texCoords;
	std::vector<GLuint> m_indices;
	std::vector<GLfloat> m_tangents;
    std::vector<GLuint> m_buffers;
    GLuint m_vao;
    GLuint m_nVerts;
};
//==============================================
#endif
//==============================================
