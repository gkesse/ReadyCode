//===============================================
#ifndef _GMatrix_
#define _GMatrix_
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
//==============================================
#endif
//==============================================
