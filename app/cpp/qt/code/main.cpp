//===============================================
#include <iostream>
//===============================================
class GMatrix;
//===============================================
int main(int argc, char** argv) {
    GMatrix lMat(3, 4);
    
    return 0;
}
//===============================================
class GMatrix {
public:
    GMatrix(int row, int col);
    ~GMatrix();

public:
    void set(int row, int col, double d);
    double get(int row, int col);
    void print() const;
    
private:
    double* m_d;
    int m_row;
    int m_col;
    int m_size;
};
//===============================================
GMatrix::GMatrix(int w, int h) {
    m_row = w;
    m_col = h;
    m_size = m_row * m_col;
    d = new double[m_size];
    printf("on cree la matrice (%d, %d)\n", m_row, m_col);
}
//===============================================
GMatrix::~GMatrix() {
    delete d;
    printf("on supprime la matrice (%d, %d)\n", m_row, m_col);
}
//===============================================
void GMatrix::set(int row, int col, double d) {
    int i = row * m_col + col;
    m_d[i] = d;
}
//===============================================
double GMatrix::get(int row, int col) const {
    int i = row * m_col + col;
    return m_d[i];
}
//===============================================
void GMatrix::print() const {
    for(int row = 0; row < m_row; row++) {
        for(int col = 0; col < m_col; col++) {
            if(m_col != 0) {printf(" ; ");}
            d = get(row, col);
            printf("%.2f", d);
        }
        printf("\n");
    }
}
//==============================================