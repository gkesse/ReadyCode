//===============================================
#ifndef _GRectangle_
#define _GRectangle_
//===============================================
#include <iostream>
//===============================================
template <typename T> 
class GRectangle {
public:
    GRectangle(const T& x1, const T& x2, const T& y1, const T& y2);
    ~GRectangle();

public:
    T width() const;
    T height() const;
    bool contain(const T& x, const T& y) const;
    T perimeter() const;
    T area() const;
    
private:
    T m_x1;
    T m_x2;
    T m_y1;
    T m_y2;
};
//===============================================
#endif
//===============================================