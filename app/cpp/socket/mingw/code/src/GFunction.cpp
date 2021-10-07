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
}
//===============================================
GFunction::~GFunction() {
    if(m_data) {delete[] m_data;}
    if(m_vertex3D) {remove();}
}
//===============================================
sGData* GFunction::data() {
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
