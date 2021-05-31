//===============================================
#ifndef _GShape_
#define _GShape_
//===============================================
#define _USE_MATH_DEFINES
//===============================================
#include <iostream>
#include <cmath>
//===============================================
class GShape {
public:
    virtual ~GShape() {}
    virtual void perimeter() const = 0;
    virtual void area() const = 0;
};
//===============================================
#endif
//===============================================
