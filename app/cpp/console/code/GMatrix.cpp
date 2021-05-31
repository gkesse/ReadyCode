//===============================================
#include "GMatrix.h"
//===============================================
GMatrix::GMatrix() {
    m_row = 0;
    m_col = 0;
    m_data = 0;
}
//===============================================
GMatrix::GMatrix(int w, int h) {
    m_row = w;
    m_col = h;
    int lSize = m_row * m_col;
    m_data = new double[lSize];
}
//===============================================
GMatrix::GMatrix(int w, int h, const std::vector<double>& data) {
    m_row = w;
    m_col = h;
    int lSize = m_row * m_col;
    m_data = new double[lSize];
    load(data);
}
//===============================================
GMatrix::GMatrix(const GMatrix& m) {
    m_row = m.m_row;
    m_col = m.m_col;
    int lSize = m_row * m_col;
    m_data = new double[lSize];
    load(m);
}
//===============================================
GMatrix::~GMatrix() {
    delete[] m_data;
}
//===============================================
void GMatrix::set(int row, int col, double d) {
    int i = row * m_col + col;
    m_data[i] = d;
}
//===============================================
double GMatrix::get(int row, int col) const {
    int i = row * m_col + col;
    return m_data[i];
}
//===============================================
void GMatrix::load(const std::vector<double>& data) {
    for(int row = 0; row < m_row; row++) {
        for(int col = 0; col < m_col; col++) {
            int i = row * m_col + col;
            double lData = data[i];
            set(row, col, lData);
        }
    }
}
//===============================================
void GMatrix::load(const GMatrix& m) {
    for(int row = 0; row < m_row; row++) {
        for(int col = 0; col < m_col; col++) {
            double lData = m.get(row, col);
            set(row, col, lData);
        }
    }
}
//===============================================
void GMatrix::add(const GMatrix& m) {
    for(int row = 0; row < m_row; row++) {
        for(int col = 0; col < m_col; col++) {
            double Ai = m.get(row, col);
            double Bi = get(row, col);
            double Ci = Ai + Bi;
            set(row, col, Ci);
        }
    }
}
//===============================================
void GMatrix::print() const {
    for(int row = 0; row < m_row; row++) {
        printf("| ");
        for(int col = 0; col < m_col; col++) {
            if(col != 0) {printf(" | ");}
            double d = get(row, col);
            printf("%3.0f", d);
        }
        printf(" |");
        printf("\n");
    }
}
//===============================================
GMatrix& GMatrix::operator=(const GMatrix& m) {
    delete this;
    m_row = m.m_row;
    m_col = m.m_col;
    int lSize = m_row * m_col;
    m_data = new double[lSize];
    load(m);
    return *this;
}
//===============================================
std::ostream& operator<<(std::ostream& os, const GMatrix& m) {
    m.print();
    return os;
}
//===============================================
GMatrix operator+(GMatrix const& a, GMatrix const& b) {
    GMatrix c(a);
    c.add(b);
    return c;
}
//===============================================
