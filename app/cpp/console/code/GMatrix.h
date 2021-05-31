//===============================================
#ifndef _GMatrix_
#define _GMatrix_
//===============================================
#include <iostream>
#include <vector>
//===============================================
class GMatrix {
public:
    GMatrix();
    GMatrix(int row, int col);
    GMatrix(int row, int col, const std::vector<double>& data);
    GMatrix(const GMatrix& m);
    ~GMatrix();

public:
    void set(int row, int col, double d);
    double get(int row, int col) const;
    void load(const std::vector<double>& data);
    void load(const GMatrix& m);
    void add(const GMatrix& m);
    void print() const;
    
public:
    GMatrix& operator=(const GMatrix& m);
    
public:
    friend std::ostream& operator<<(std::ostream& os, const GMatrix& m);
    friend GMatrix operator+(GMatrix const& a, GMatrix const& b);
    
private:
    double* m_data;
    int m_row;
    int m_col;
};
//===============================================
#endif
//==============================================
