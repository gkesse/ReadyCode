//===============================================
#include "GFunction.h"
//===============================================
GFunction::GFunction() {
    m_data = 0;
    m_size = 0;
}
//===============================================
GFunction::~GFunction() {
    if(m_data != 0) {delete m_data;}
}
//===============================================
sGData* GFunction::data() {
    return m_data;
}
//===============================================
int GFunction::size() {
    return m_size;
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
void GFunction::zMinMax(float& _zmin, float& _zmax) {
    _zmin = m_data[0].z;
    _zmax = m_data[0].z;

    for(int i = 0; i < m_size; i++){
        sGData lData = m_data[i];
        if(lData.z < _zmin) {_zmin = lData.z;}
        if(lData.z > _zmax) {_zmax = lData.z;}
    }
}
//===============================================
