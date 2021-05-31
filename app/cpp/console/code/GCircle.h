//===============================================
#ifndef _GCircle_
#define _GCircle_
//===============================================
#include "GShape.h"
//===============================================
class GCircle : public GShape {
public:
    GCircle(double r);
    ~GCircle();

public:
    void perimeter() const;
    void area() const;
    
private:
    double m_r;
};
//===============================================
#endif
//===============================================