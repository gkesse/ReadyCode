//===============================================
#ifndef _GFunction_
#define _GFunction_
//===============================================
#include "GInclude.h"
//===============================================
class GFunction {
public:
    GFunction();
    ~GFunction();
    sGData* data();
    sGVertex*** vertex3D();
    void allocate(int _xsize, int _ysize, int _zsize);
    void remove();
    int size();
    int xsize();
    int ysize();
    int zsize();
    sGData* sinus(float _max, float _phase, int _size, float _range);
    sGData* gaussian2D(int _xSize, int _ySize, float _sigma);
    void mcml(const char* _filename, int _xsize, int _ysize, int _zsize, const sGColor& _color);
    void zMinMax(float& _zmin, float& _zmax);
    void zMinMax2(float& _zmin, float& _zmax);

private:
    sGData* m_data;
    sGVertex*** m_vertex3D;
    float*** m_float3D;
    int m_size;
    int m_xsize;
    int m_ysize;
    int m_zsize;
};
//==============================================
#endif
//==============================================
