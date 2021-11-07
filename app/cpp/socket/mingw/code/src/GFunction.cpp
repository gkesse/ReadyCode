//===============================================
#include "GFunction.h"
#include "GFile.h"
#include "GOpenGL.h"
//===============================================
GFunction::GFunction() {
    m_sinus = 0;
    m_gaussian2D = 0;
    m_mcmlPoint = 0;
    m_mcmlData = 0;
    m_size = 0;
    m_xsize = 0;
    m_ysize = 0;
    m_zsize = 0;
    m_noise = 0;
}
//===============================================
GFunction::~GFunction() {

}
//===============================================
void GFunction::deletes() {
    if(m_sinus) {
        delete[] m_sinus;
        m_sinus = 0;
    }
    if(m_gaussian2D) {
        delete[] m_gaussian2D;
        m_gaussian2D = 0;
    }
    if(m_mcmlData) {
        delete[] m_mcmlData;
        m_mcmlData = 0;
    }
}
//===============================================
sGVertex*** GFunction::vertex3D() {
    return m_mcmlPoint;
}
//===============================================
void GFunction::remove() {
    for(int i = 0; i < m_xsize; i++) {
        for(int j = 0; j < m_ysize; j++) {
            delete[] m_mcmlPoint[i][j];
            delete[] m_mcmlData[i][j];
        }
        delete[] m_mcmlPoint[i];
        delete[] m_mcmlData[i];
    }
    delete[] m_mcmlPoint;
    delete[] m_mcmlData;
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
void GFunction::sinus(float _max, float _phase, int _size, float _range) {
    m_size = _size;
    m_sinus = new sGPoint[m_size];
    for(int i = 0; i < _size; i++) {
        m_sinus[i].x = ((float)i/_size) * _range - _range/2.f;
        m_sinus[i].y = _max * cosf(m_sinus[i].x * 3.14f + _phase);
    }
}
//===============================================
sGPoint* GFunction::sinus() const {
    return m_sinus;
}
//===============================================
void GFunction::gaussian2D(int _xsize, int _ysize, float _sigma) {
    m_size = _xsize * _ysize;
    m_sinus = new sGPoint[m_size];
    int lCount = 0;
    for(int x = -_xsize/2; x < _xsize/2; x += 1) {
        for(int y = -_ysize/2; y < _ysize/2; y += 1) {
            float lX = 2.f*x / _xsize;
            float lY = 2.f*y / _ysize;
            float lZ = exp(-0.5f * (lX * lX) / (_sigma * _sigma) - 0.5f * (lY * lY)/(_sigma * _sigma))/(_sigma * _sigma * 2.f * M_PI);
            m_sinus[lCount].x = lX;
            m_sinus[lCount].y = lY;
            m_sinus[lCount].z = lZ;
            lCount++;
        }
    }
}
//===============================================
sGPoint* GFunction::gaussian2D() const {
    return m_gaussian2D;
}
//===============================================
void GFunction::mcml(int _xsize, int _ysize, int _zsize) {
    m_xsize = _xsize; m_ysize = _ysize; m_zsize = _zsize;
    m_mcmlPoint = new sGVertex**[m_xsize];
    m_mcmlData = new float**[m_xsize];
    for(int i = 0; i < m_xsize; i++) {
        m_mcmlPoint[i] = new sGVertex*[m_ysize];
        m_mcmlData[i] = new float*[m_ysize];
        for(int j = 0; j < m_ysize; j++) {
            m_mcmlPoint[i][j] = new sGVertex[m_zsize];
            m_mcmlData[i][j] = new float[m_zsize];
        }
    }
}
//===============================================
void GFunction::mcml(const char* _filename, int _xsize, int _ysize, int _zsize, const sGColor& _color) {
    GFile lFile;
    lFile.filename(_filename);
    lFile.open();
    mcml(_xsize, _ysize, _zsize);
    float lData, lMin, lMax;
    GOpenGL _lOpenGL;

    for(int x = 0; x < _xsize; x++){
        for(int z = 0; z < _zsize; z++){
            for(int y = 0; y < _ysize; y++) {
                if(lFile.read(lData) != EOF) {
                    lData = log(lData + 1);
                    m_mcmlData[x][y][z] = lData;
                    m_mcmlPoint[x][y][z].d.x = (float)(x - _xsize / 2.f) / _xsize;
                    m_mcmlPoint[x][y][z].d.y = (float)(y - _ysize / 2.f) / _ysize;
                    m_mcmlPoint[x][y][z].d.z = (float)(z - _zsize / 2.f) / _zsize * 2.f;
                }
            }
        }
    }

    zMinMax2(lMin, lMax);

    for(int z = 0; z < _zsize; z++){
        for(int x = 0; x < _xsize; x++){
            for(int y = 0; y < _ysize; y++) {
                float lData = m_mcmlData[x][y][z];
                sGColor lColor = _lOpenGL.heatMap(lData, lMin, lMax, _color);
                m_mcmlPoint[x][y][z].c.r = lColor.r;
                m_mcmlPoint[x][y][z].c.g = lColor.g;
                m_mcmlPoint[x][y][z].c.b = lColor.b;
            }
        }
    }

    lFile.close();
}
//===============================================
void GFunction::zMinMax(float& _zmin, float& _zmax) {
    _zmin = m_sinus[0].z;
    _zmax = m_sinus[0].z;

    for(int i = 0; i < m_size; i++) {
        sGPoint lData = m_sinus[i];
        if(lData.z < _zmin) {_zmin = lData.z;}
        if(lData.z > _zmax) {_zmax = lData.z;}
    }
}
//===============================================
void GFunction::zMinMax2(float& _zmin, float& _zmax) {
    _zmin = m_mcmlData[0][0][0];
    _zmax = m_mcmlData[0][0][0];

    for(int x = 0; x < m_xsize; x++) {
        for(int y = 0; y < m_ysize; y++) {
            for(int z = 0; z < m_zsize; z++) {
                float lData = m_mcmlData[x][y][z];
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

    float xFactor = 1.f / (lWidth - 1);
    float yFactor = 1.f / (lHeight - 1);

    for(int row = 0; row < lHeight; row++) {
        for(int col = 0 ; col < lWidth; col++) {
            float x = xFactor * col;
            float y = yFactor * row;
            float lSum = 0.f;
            float lFreq = _baseFreq;
            float lPersistence = _persistence;
            for(int oct = 0; oct < 4; oct++) {
                glm::vec2 p(x * lFreq, y * lFreq);
                float lValue = 0.f;

                if (_periodic) {
                    lValue = glm::perlin(p, glm::vec2(lFreq)) * lPersistence;
                } else {
                    lValue = glm::perlin(p) * lPersistence;
                }

                lSum += lValue;

                float lResult = (lSum + 1.f) / 2.f;

                lResult = lResult > 1.f ? 1.f : lResult;
                lResult = lResult < 0.f ? 0.f : lResult;

                m_noise[((row * lWidth + col) * 4) + oct] = (GLubyte) ( lResult * 255.f );
                lFreq *= 2.f;
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
void GFunction::deleteNoise() {
    if(m_noise) {
        delete[] m_noise;
        m_noise = 0;
    }
}
//===============================================
