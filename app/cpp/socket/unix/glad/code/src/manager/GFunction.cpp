//===============================================
#include "GFunction.h"
#include "GFile.h"
#include "GOpenGL.h"
//===============================================
GFunction::GFunction() {
    m_data = 0;
    m_vertex3D = 0;
    m_float3D = 0;
    m_size = 0;
    m_xsize = 0;
    m_ysize = 0;
    m_zsize = 0;
    m_noise = 0;
    m_velocity = 0;
    m_times = 0;
}
//===============================================
GFunction::~GFunction() {
    if(m_data) {delete[] m_data;}
    if(m_vertex3D) {remove();}
    deletes();
}
//===============================================
sGData* GFunction::_data() {
    return m_data;
}
//===============================================
sGVertex*** GFunction::vertex3D() {
    return m_vertex3D;
}
//===============================================
void GFunction::allocate(int _xsize, int _ysize, int _zsize) {
    m_xsize = _xsize; m_ysize = _ysize; m_zsize = _zsize;
    m_vertex3D = new sGVertex**[m_xsize];
    m_float3D = new float**[m_xsize];
    for(int i = 0; i < m_xsize; i++) {
        m_vertex3D[i] = new sGVertex*[m_ysize];
        m_float3D[i] = new float*[m_ysize];
        for(int j = 0; j < m_ysize; j++) {
            m_vertex3D[i][j] = new sGVertex[m_zsize];
            m_float3D[i][j] = new float[m_zsize];
        }
    }
}
//===============================================
void GFunction::remove() {
    for(int i = 0; i < m_xsize; i++) {
        for(int j = 0; j < m_ysize; j++) {
            delete[] m_vertex3D[i][j];
            delete[] m_float3D[i][j];
        }
        delete[] m_vertex3D[i];
        delete[] m_float3D[i];
    }
    delete[] m_vertex3D;
    delete[] m_float3D;
}
//===============================================
int GFunction::size() {
    return m_size;
}
//===============================================
int GFunction::xsize() {
    return m_xsize;
}
//===============================================
int GFunction::ysize() {
    return m_ysize;
}
//===============================================
int GFunction::zsize() {
    return m_zsize;
}
//===============================================
sGData* GFunction::sinus(float _max, float _phase, int _size, float _range) {
    m_size = _size;
    m_data = new sGData[m_size];
    for(int i = 0; i < _size; i++) {
        m_data[i].x = ((float)i/_size) * _range - _range/2.0f;
        m_data[i].y = _max * cosf(m_data[i].x * 3.14f + _phase);
    }
    return m_data;
}
//===============================================
sGData* GFunction::gaussian2D(int _xSize, int _ySize, float _sigma) {
    m_size = _xSize*_ySize;
    m_data = new sGData[m_size];
    int lCount = 0;
    for(int x = -_xSize/2; x < _xSize/2; x += 1) {
        for(int y = -_ySize/2; y < _ySize/2; y += 1) {
            float lX = 2.0f*x / _xSize;
            float lY = 2.0f*y / _ySize;
            float lZ = exp(-0.5f * (lX * lX) / (_sigma * _sigma) - 0.5f * (lY * lY)/(_sigma * _sigma))/(_sigma * _sigma * 2.0f * M_PI);
            m_data[lCount].x = lX;
            m_data[lCount].y = lY;
            m_data[lCount].z = lZ;
            lCount++;
        }
    }
    return m_data;
}
//===============================================
void GFunction::mcml(const char* _filename, int _xsize, int _ysize, int _zsize, const sGColor& _color) {
    GFile lFile;
    lFile.filename(_filename);
    lFile.open();
    allocate(_xsize, _ysize, _zsize);
    float lData, lMin, lMax;
    GOpenGL _lOpenGL;

    for(int x = 0; x < _xsize; x++){
        for(int z = 0; z < _zsize; z++){
            for(int y = 0; y < _ysize; y++) {
                if(lFile.read(lData) != EOF) {
                    lData = log(lData + 1);
                    m_float3D[x][y][z] = lData;
                    m_vertex3D[x][y][z].x = (float)(x - _xsize / 2.0f) / _xsize;
                    m_vertex3D[x][y][z].y = (float)(y - _ysize / 2.0f) / _ysize;
                    m_vertex3D[x][y][z].z = (float)(z - _zsize / 2.0f) / _zsize * 2.0f;
                }
            }
        }
    }

    zMinMax2(lMin, lMax);

    for(int z = 0; z < _zsize; z++){
        for(int x = 0; x < _xsize; x++){
            for(int y = 0; y < _ysize; y++) {
                float lData = m_float3D[x][y][z];
                sGColor lColor = _lOpenGL.heatMap(lData, lMin, lMax, _color);
                m_vertex3D[x][y][z].r = lColor.r;
                m_vertex3D[x][y][z].g = lColor.g;
                m_vertex3D[x][y][z].b = lColor.b;
            }
        }
    }

    lFile.close();
}
//===============================================
void GFunction::zMinMax(float& _zmin, float& _zmax) {
    _zmin = m_data[0].z;
    _zmax = m_data[0].z;

    for(int i = 0; i < m_size; i++) {
        sGData lData = m_data[i];
        if(lData.z < _zmin) {_zmin = lData.z;}
        if(lData.z > _zmax) {_zmax = lData.z;}
    }
}
//===============================================
void GFunction::zMinMax2(float& _zmin, float& _zmax) {
    _zmin = m_float3D[0][0][0];
    _zmax = m_float3D[0][0][0];

    for(int x = 0; x < m_xsize; x++) {
        for(int y = 0; y < m_ysize; y++) {
            for(int z = 0; z < m_zsize; z++) {
                float lData = m_float3D[x][y][z];
                if(lData < _zmin) {_zmin = lData;}
                if(lData > _zmax) {_zmax = lData;}
            }
        }
    }
}
//===============================================
void GFunction::noise(float _baseFreq, float _persistence, int _width, int _height, bool _periodic) {
    int lWidth = _width;
    int lHeight = _height;

    m_noise = new GLubyte[lWidth * lHeight * 4];

    float xFactor = 1.0f / (lWidth - 1);
    float yFactor = 1.0f / (lHeight - 1);

    for(int row = 0; row < lHeight; row++) {
        for(int col = 0 ; col < lWidth; col++) {
            float x = xFactor * col;
            float y = yFactor * row;
            float lSum = 0.0f;
            float lFreq = _baseFreq;
            float lPersistence = _persistence;
            for(int oct = 0; oct < 4; oct++) {
                glm::vec2 p(x * lFreq, y * lFreq);
                float lValue = 0.0f;

                if (_periodic) {
                    lValue = glm::perlin(p, glm::vec2(lFreq)) * lPersistence;
                } else {
                    lValue = glm::perlin(p) * lPersistence;
                }

                lSum += lValue;

                float lResult = (lSum + 1.0f) / 2.0f;

                lResult = lResult > 1.0f ? 1.0f : lResult;
                lResult = lResult < 0.0f ? 0.0f : lResult;

                m_noise[((row * lWidth + col) * 4) + oct] = (GLubyte) ( lResult * 255.0f );
                lFreq *= 2.0f;
                lPersistence *= _persistence;
            }
        }
    }
}
//===============================================
void GFunction::noise(const sGNoise& _noise) {
    noise(_noise.baseFreq, _noise.persistence, _noise.width, _noise.height, _noise.periodic);
}
//===============================================
GLubyte* GFunction::noise() {
    return m_noise;
}
//===============================================
void GFunction::deletes() {
    if(m_noise) {
        delete[] m_noise;
        m_noise = 0;
    }
    if(m_velocity) {
        delete[] m_velocity;
        m_velocity = 0;
    }
    if(m_times) {
        delete[] m_times;
        m_times = 0;
    }
}
//===============================================
void GFunction::velocity(int _nParticles, float _vmin, float _vmax, float _fovZ) {
    glm::vec3 v(0.0f);
    float velocity, theta, phi;
    m_velocity = new GLfloat[_nParticles * 3];
    for(GLuint i = 0; i < _nParticles; i++ ) {
        theta = glm::mix(0.0f, glm::pi<float>() * _fovZ, randFloat());
        phi = glm::mix(0.0f, glm::two_pi<float>(), randFloat());

        v.x = sinf(theta) * cosf(phi);
        v.y = cosf(theta);
        v.z = sinf(theta) * sinf(phi);

        velocity = glm::mix(_vmin, _vmax, randFloat());
        v = glm::normalize(v) * velocity;

        m_velocity[3*i + 0] = v.x;
        m_velocity[3*i + 1] = v.y;
        m_velocity[3*i + 2] = v.z;
    }
}
//===============================================
GLfloat* GFunction::velocity() {
    return m_velocity;
}
//===============================================
void GFunction::times(int _nParticles, float _rate) {
    m_times = new GLfloat[_nParticles];
    float lTime = 0.0f;
    for( GLuint i = 0; i < _nParticles; i++ ) {
        m_times[i] = lTime;
        lTime += _rate;
    }
}
//===============================================
GLfloat* GFunction::times() {
    return m_times;
}
//===============================================
float GFunction::randFloat() {
    return ((float)rand() / RAND_MAX);
}
//===============================================
