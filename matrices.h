#ifndef MATRICES_H_
#define MATRICES_H_

#include <iostream>

class matrix {
    int m_row; //number or rows
    int m_col; //number of columns

    double **m_el;
    bool m_filled {false};

    public:

    //Constructors
    matrix();
    ~matrix();
    matrix(int,int);
    matrix(const matrix&); //copy

    //Redefinition of operators
    matrix operator +();
    matrix operator -();

    matrix operator+(matrix);
    matrix operator-(matrix);
    matrix operator*(matrix);

    matrix& operator=(const matrix&);
    friend std::ostream& operator<< (std::ostream &, const matrix&);

    //Getters and setters
    int get_row();
    int get_col();
    int is_filled();
    double** get_el();
    void set_row(int);
    void set_col(int);
    void set_el(double**);

    //Methods to fill the matrix
    void fill_matrix(double**);
    void fill_matrix();


    //Linear algebra methods
    matrix transpose ();
    matrix invert ();
    //double determinant(matrix);
    //matrix triangular(const matrix);
    matrix swap_rows(int,int);
    matrix sum_rows(int,int,double);

    int find_most_zeros();

};

#endif // MATRICES_H_
