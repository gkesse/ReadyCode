//===============================================
#include "GObject.h"
//===============================================
GObject::GObject() {
	m_vao = 0;
	m_nVerts = 0;
}
//===============================================
GObject::~GObject() {
	deletes();
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
			m_points[idx] = r * cu;
			m_points[idx + 1] = r * su;
			m_points[idx + 2] = _innerRadius * sv;
			m_normals[idx] = cv * cu * r;
			m_normals[idx + 1] = cv * su * r;
			m_normals[idx + 2] = sv * r;
			m_texCoords[tidx] = u / glm::two_pi<float>();
			m_texCoords[tidx + 1] = v / glm::two_pi<float>();
			tidx += 2;

			float len = sqrt(
					m_normals[idx] * m_normals[idx] +
					m_normals[idx+1] * m_normals[idx+1] +
					m_normals[idx+2] * m_normals[idx+2]
			);

			m_normals[idx] /= len;
			m_normals[idx+1] /= len;
			m_normals[idx+2] /= len;
			idx += 3;
		}
	}

	idx = 0;
	for( GLuint ring = 0; ring < _nrings; ring++ ) {
		GLuint ringStart = ring * _nsides;
		GLuint nextRingStart = (ring + 1) * _nsides;
		for( GLuint side = 0; side < _nsides; side++ ) {
			int nextSide = (side+1) % _nsides;
			m_indices[idx] = (ringStart + side);
			m_indices[idx+1] = (nextRingStart + side);
			m_indices[idx+2] = (nextRingStart + nextSide);
			m_indices[idx+3] = ringStart + side;
			m_indices[idx+4] = nextRingStart + nextSide;
			m_indices[idx+5] = (ringStart + nextSide);
			idx += 6;
		}
	}
}
//===============================================
void GObject::init(){
	if(!m_buffers.empty()) deletes();
	if(m_indices.empty() || m_points.empty() || m_normals.empty()) return;

	m_nVerts = (GLuint)m_indices.size();

	GLuint indexBuf = 0, posBuf = 0, normBuf = 0, tcBuf = 0, tangentBuf = 0;
	glGenBuffers(1, &indexBuf);
	m_buffers.push_back(indexBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &posBuf);
	m_buffers.push_back(posBuf);
	glBindBuffer(GL_ARRAY_BUFFER, posBuf);
	glBufferData(GL_ARRAY_BUFFER, m_points.size() * sizeof(GLfloat), m_points.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &normBuf);
	m_buffers.push_back(normBuf);
	glBindBuffer(GL_ARRAY_BUFFER, normBuf);
	glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(GLfloat), m_normals.data(), GL_STATIC_DRAW);

	if(!m_texCoords.empty()) {
		glGenBuffers(1, &tcBuf);
		m_buffers.push_back(tcBuf);
		glBindBuffer(GL_ARRAY_BUFFER, tcBuf);
		glBufferData(GL_ARRAY_BUFFER, m_texCoords.size() * sizeof(GLfloat), m_texCoords.data(), GL_STATIC_DRAW);
	}

	if(!m_tangents.empty()) {
		glGenBuffers(1, &tangentBuf);
		m_buffers.push_back(tangentBuf);
		glBindBuffer(GL_ARRAY_BUFFER, tangentBuf);
		glBufferData(GL_ARRAY_BUFFER, m_tangents.size() * sizeof(GLfloat), m_tangents.data(), GL_STATIC_DRAW);
	}

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuf);

	glBindBuffer(GL_ARRAY_BUFFER, posBuf);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, normBuf);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	if(!m_texCoords.empty()) {
		glBindBuffer(GL_ARRAY_BUFFER, tcBuf);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);
	}

	if(!m_tangents.empty()) {
		glBindBuffer(GL_ARRAY_BUFFER, tangentBuf);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(3);
	}

	glBindVertexArray(0);
}
//===============================================
void GObject::deletes() {
	if(m_buffers.size() > 0) {
		glDeleteBuffers((GLsizei)m_buffers.size(), m_buffers.data());
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
    glDrawElements(GL_TRIANGLES, m_nVerts, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
//===============================================
