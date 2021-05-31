//===============================================
#include "GRectangle.h"
//===============================================
template <typename T>
GRectangle<T>::GRectangle(const T& x1, const T& x2, const T& y1, const T& y2) {
    m_x1 = x1;
    m_x2 = x2;
    m_y1 = y1;
    m_y2 = y2;
    T lTmp;
    if(m_x1 > m_x2) {lTmp = m_x1; m_x1 = m_x2; m_x2 = lTmp;}
    if(m_y1 > m_y2) {lTmp = m_y1; m_y1 = m_y2; m_y2 = lTmp;}
}
//===============================================
template <typename T>
GRectangle<T>::~GRectangle() {

}
//===============================================
template <typename T>
T GRectangle<T>::width() const {
    T lWidth = m_x2 - m_x1;
    return lWidth;
}
//===============================================
template <typename T>
T GRectangle<T>::height() const {
    T lHeight = m_y2 - m_y1;
    return lHeight;
}
//===============================================
template <typename T>
bool GRectangle<T>::contain(const T& x, const T& y) const {
    if(x < m_x1 || x > m_x2) {return 0;}
    if(y < m_y1 || y > m_y2) {return 0;}
    return 1;
}
//===============================================
template <typename T>
T GRectangle<T>::perimeter() const {
    T lWidth = width();
    T lHeight = height();
    T lPerimeter = 2 * (lWidth + lHeight);
    return lPerimeter;
}
//===============================================
template <typename T>
T GRectangle<T>::area() const {
    T lWidth = width();
    T lHeight = height();
    T lArea = lWidth * lHeight;
    return lArea;
}
//===============================================
template class GRectangle<int>;
//===============================================
