//===============================================
#include "GObject.h"
#include "GFunction.h"
//===============================================
GObject::GObject() {
    m_vao = 0;
    m_nIndices = 0;
    m_nPoints = 0;
}
//===============================================
GObject::~GObject() {
    clear();
}
//===============================================
void GObject::torus(GLfloat _outerRadius, GLfloat _innerRadius, GLuint _nsides, GLuint _nrings) {
    GLuint faces = _nsides * _nrings;
    int nVerts  = _nsides * (_nrings + 1);

    m_points.resize(3 * nVerts);
    m_normals.resize(3 * nVerts);
    m_texCoords.resize(2 * nVerts);
    m_indices.resize(6 * faces);

    float ringFactor = glm::two_pi<float>() / _nrings;
    float sideFactor = glm::two_pi<float>() / _nsides;
    int idx = 0, tidx = 0;

    for(GLuint ring = 0; ring <= _nrings; ring++) {
        float u = ring * ringFactor;
        float cu = cos(u);
        float su = sin(u);
        for( GLuint side = 0; side < _nsides; side++ ) {
            float v = side * sideFactor;
            float cv = cos(v);
            float sv = sin(v);
            float r = (_outerRadius + _innerRadius * cv);
            m_points[idx + 0] = r * cu;
            m_points[idx + 1] = r * su;
            m_points[idx + 2] = _innerRadius * sv;
            m_normals[idx + 0] = cv * cu * r;
            m_normals[idx + 1] = cv * su * r;
            m_normals[idx + 2] = sv * r;
            m_texCoords[tidx + 0] = u / glm::two_pi<float>();
            m_texCoords[tidx + 1] = v / glm::two_pi<float>();
            tidx += 2;

            float len = sqrt(
                    m_normals[idx + 0] * m_normals[idx] +
                    m_normals[idx + 1] * m_normals[idx+1] +
                    m_normals[idx + 2] * m_normals[idx+2]
            );

            m_normals[idx + 0] /= len;
            m_normals[idx + 1] /= len;
            m_normals[idx + 2] /= len;
            idx += 3;
        }
    }

    idx = 0;
    for( GLuint ring = 0; ring < _nrings; ring++ ) {
        GLuint ringStart = ring * _nsides;
        GLuint nextRingStart = (ring + 1) * _nsides;
        for( GLuint side = 0; side < _nsides; side++ ) {
            int nextSide = (side+1) % _nsides;
            m_indices[idx + 0] = (ringStart + side);
            m_indices[idx + 1] = (nextRingStart + side);
            m_indices[idx + 2] = (nextRingStart + nextSide);
            m_indices[idx + 3] = ringStart + side;
            m_indices[idx + 4] = nextRingStart + nextSide;
            m_indices[idx + 5] = (ringStart + nextSide);
            idx += 6;
        }
    }
}
//===============================================
void GObject::plane(float _xsize, float _zsize, int _xdivs, int _zdivs, float _smax, float _tmax) {
    m_points.resize(3 * (_xdivs + 1) * (_zdivs + 1));
    m_normals.resize(3 * (_xdivs + 1) * (_zdivs + 1));
    m_texCoords.resize(2 * (_xdivs + 1) * (_zdivs + 1));
    m_indices.resize(6 * _xdivs * _zdivs);

    float x2 = _xsize / 2.0f;
    float z2 = _zsize / 2.0f;
    float iFactor = (float)_zsize / _zdivs;
    float jFactor = (float)_xsize / _xdivs;
    float texi = _smax / _zdivs;
    float texj = _tmax / _xdivs;
    float x, z;
    int vidx = 0, tidx = 0;
    for( int i = 0; i <= _zdivs; i++ ) {
        z = iFactor * i - z2;
        for( int j = 0; j <= _xdivs; j++ ) {
            x = jFactor * j - x2;
            m_points[vidx + 0] = x;
            m_points[vidx + 1] = 0.0f;
            m_points[vidx + 2] = z;
            m_normals[vidx + 0] = 0.0f;
            m_normals[vidx + 1] = 1.0f;
            m_normals[vidx + 2] = 0.0f;

            m_texCoords[tidx + 0] = j * texi;
            m_texCoords[tidx + 1] = i * texj;

            vidx += 3;
            tidx += 2;
        }
    }

    GLuint rowStart, nextRowStart;
    int idx = 0;
    for( int i = 0; i < _zdivs; i++ ) {
        rowStart = (GLuint)( i * (_xdivs+1) );
        nextRowStart = (GLuint)( (i+1) * (_xdivs+1));
        for( int j = 0; j < _xdivs; j++ ) {
            m_indices[idx + 0] = rowStart + j;
            m_indices[idx + 1] = nextRowStart + j;
            m_indices[idx + 2] = nextRowStart + j + 1;
            m_indices[idx + 3] = rowStart + j;
            m_indices[idx + 4] = nextRowStart + j + 1;
            m_indices[idx + 5] = rowStart + j + 1;
            idx += 6;
        }
    }
}
//===============================================
void GObject::particles(int _nParticles) {
	GFunction lFunction;
	lFunction.velocity(_nParticles);
	lFunction.times(_nParticles);

	m_nPoints = _nParticles;

	GLuint lVelocityBuf = 0, lTimesBuf = 0;

    glGenBuffers(1, &lVelocityBuf);
    m_buffers.push_back(lVelocityBuf);
    glBindBuffer(GL_ARRAY_BUFFER, lVelocityBuf);
    glBufferData(GL_ARRAY_BUFFER, _nParticles * 3 * sizeof(GLfloat), lFunction.velocity(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3, (void*)(0));
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &lTimesBuf);
    m_buffers.push_back(lTimesBuf);
    glBindBuffer(GL_ARRAY_BUFFER, lTimesBuf);
    glBufferData(GL_ARRAY_BUFFER, _nParticles * sizeof(GLfloat), lFunction.times(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 1, (void*)(0));
    glEnableVertexAttribArray(1);

    lFunction.deletes();
    glBindVertexArray(0);
}
//===============================================
void GObject::init(){
    if(!m_buffers.empty()) deletes();
    if(m_indices.empty() || m_points.empty() || m_normals.empty()) return;

    m_nIndices = (GLuint)m_indices.size();

    GLuint indexBuf = 0, posBuf = 0, normBuf = 0, tcBuf = 0, tangentBuf = 0;

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &indexBuf);
    m_buffers.push_back(indexBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &posBuf);
    m_buffers.push_back(posBuf);
    glBindBuffer(GL_ARRAY_BUFFER, posBuf);
    glBufferData(GL_ARRAY_BUFFER, m_points.size() * sizeof(GLfloat), m_points.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &normBuf);
    m_buffers.push_back(normBuf);
    glBindBuffer(GL_ARRAY_BUFFER, normBuf);
    glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(GLfloat), m_normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glEnableVertexAttribArray(1);

    if(!m_texCoords.empty()) {
        glGenBuffers(1, &tcBuf);
        m_buffers.push_back(tcBuf);
        glBindBuffer(GL_ARRAY_BUFFER, tcBuf);
        glBufferData(GL_ARRAY_BUFFER, m_texCoords.size() * sizeof(GLfloat), m_texCoords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));
        glEnableVertexAttribArray(2);
    }

    if(!m_tangents.empty()) {
        glGenBuffers(1, &tangentBuf);
        m_buffers.push_back(tangentBuf);
        glBindBuffer(GL_ARRAY_BUFFER, tangentBuf);
        glBufferData(GL_ARRAY_BUFFER, m_tangents.size() * sizeof(GLfloat), m_tangents.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, (void*)(0));
        glEnableVertexAttribArray(3);
    }

    glBindVertexArray(0);
}
//===============================================
void GObject::clear() {
    m_indices.clear();
    m_points.clear();
    m_normals.clear();
    m_texCoords.clear();
    m_tangents.clear();
}
//===============================================
void GObject::deletes() {
    if(m_buffers.size() > 0) {
        glDeleteBuffers(m_buffers.size(), m_buffers.data());
        m_buffers.clear();
    }
    if(m_vao != 0) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
}
//===============================================
void GObject::render() const {
    if(m_vao == 0) return;
    glBindVertexArray(m_vao);
    if(m_nIndices) {
    	glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, 0);
    }
    if(m_nPoints) {
    	glDrawArrays(GL_POINTS, 0, m_nPoints);
    }
    glBindVertexArray(0);
}
//===============================================
