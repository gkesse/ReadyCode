//===============================================
#ifndef _GFunction_
#define _GFunction_
//===============================================
#include "GInclude.h"
#include "GStruct.h"
//===============================================
class GFunction {
public:
    GFunction();
    ~GFunction();
    sGData* _data();
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
    void noise(float _baseFreq, float _persistence, int _width, int _height, bool _periodic);
    void noise(const sGNoise& _noise);
    GLubyte* noise();
    void deletes();
    void velocity(int _nParticles, float _vmin = 1.25f, float _vmax = 1.5f, float _fovZ = 1.f/6);
    GLfloat* velocity();
    void times(int _nParticles, float _rate = 0.00075f);
	GLfloat* times();
    float randFloat();

private:
    sGData* m_data;
    sGVertex*** m_vertex3D;
    float*** m_float3D;
    int m_size;
    int m_xsize;
    int m_ysize;
    int m_zsize;
    GLubyte* m_noise;
    GLfloat* m_velocity;
    GLfloat* m_times;
};
//==============================================
#endif
//==============================================
