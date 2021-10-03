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
    int size();
    sGData* sinus(float _max, float _phase, int _size, float _range);
    sGData* gaussian2D(int _xSize, int _ySize, float _sigma);
    void zMinMax(float& _zmin, float& _zmax)

private:
    sGData* m_data;
    int m_size;
};
//==============================================
#endif
//==============================================
