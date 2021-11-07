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
    void deletes();
    sGVertex*** vertex3D();
    void remove();
    int size();
    int xsize();
    int ysize();
    int zsize();
    void sinus(float _max, float _phase, int _size, float _range);
    sGPoint* sinus() const;
    void gaussian2D(int _xSize, int _ySize, float _sigma);
    sGPoint* gaussian2D() const;
    void mcml(int _xsize, int _ysize, int _zsize);
    void mcml(const char* _filename, int _xsize, int _ysize, int _zsize, const sGColor& _color);
    void zMinMax(float& _zmin, float& _zmax);
    void zMinMax2(float& _zmin, float& _zmax);
    void noise(float _baseFreq, float _persistence, int _width, int _height, bool _periodic);
    void noise(const sGNoise& _noise);
    GLubyte* noise();
    void deleteNoise();

private:
    sGPoint* m_sinus;
    sGPoint* m_gaussian2D;
    sGVertex*** m_mcmlPoint;
    GLfloat*** m_mcmlData;
    int m_size;
    int m_xsize;
    int m_ysize;
    int m_zsize;
    GLubyte* m_noise;
};
//==============================================
#endif
//==============================================
