//===============================================
#include "GCircle.h"
//===============================================
GCircle::GCircle(double r) {
    m_r = r;
}
//===============================================
GCircle::~GCircle() {
    printf("[Circle] on supprime le cercle (r : %.0f)\n", m_r);
}
//===============================================
void GCircle::perimeter() const {
    double lPerimeter = 2 * M_PI * m_r;
    printf("[Circle] Perimetre (r : %.0f) : %.0f (m)\n", m_r, lPerimeter);
}
//===============================================
void GCircle::area() const {
    double lArea = M_PI * m_r * m_r;
    printf("[Circle] Aire (r : %.0f) : %.0f (m2)\n", m_r, lArea);
}
//===============================================
