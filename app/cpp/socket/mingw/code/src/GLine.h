//===============================================
#ifndef _GLine_
#define _GLine_
//===============================================
#include "GInclude.h"
//===============================================
class GLine {
public:
    GLine();
    GLine(float _x1, float _y1, float _x2, float _y2);
    ~GLine();
    void computeA();
    void computeB();
    float valY(float _x);
    float valX(float _y);

    
private:
    float m_x1;
    float m_y1;
    float m_x2;
    float m_y2;
    float m_a;
    float m_b;
};
//==============================================
#endif
//==============================================
