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
    void plane(float _xsize, float _zsize, int _xdivs, int _zdivs, float _smax, float _tmax);
    void particles(int _nParticles = 8000);
    void init();
    void clear();
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
    GLuint m_nIndices;
    GLuint m_nPoints;
};
//==============================================
#endif
//==============================================
