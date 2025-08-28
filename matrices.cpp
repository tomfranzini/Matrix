#include "matrices.h"

#include<iostream>
#include<random>
#include<cstdlib>

matrix::matrix(){
    m_row=1;
    m_col=1;

    m_el = new double *[1];
    m_el[0] = new double[1];

    m_el[0][0] = 0;

};


matrix::matrix(int n,int m){
    m_row=n;
    m_col=m;

    m_el = new double *[n];
    for(int k=0;k<n;k++){
        m_el[k] = new double[m] {};
    };

};

matrix::~matrix() {
    for (int i = 0; i < m_row; i++) {
        delete[] m_el[i];
    }
    delete[] m_el;
};

/*
** The copy constructor is needed to explicitly tell the
** compiler how to copy the double array.
*/

matrix::matrix(const matrix& other)
    : m_row(other.m_row), m_col(other.m_col){
    this->m_el = new double*[m_row];
    for(int i = 0; i < m_row; i++) {
        m_el[i] = new double[m_col];
        for (int j = 0; j < m_col; j++) {
            this->m_el[i][j] = other.m_el[i][j]; // copy values, not pointer
        };
    };
};

int matrix::get_row(){
    return m_row;
};

int matrix::get_col(){
    return m_col;
};

int matrix::is_filled(){
    return m_filled;
};

double** matrix::get_el(){
    return m_el;
};

void matrix::set_row(int my_n){
    m_row = my_n;
};

void matrix::set_col(int my_m){
    m_col = my_m;
};

void matrix::set_el(double** my_el){
    m_el = my_el;
}

matrix matrix::operator +(){
    return *this;
};

matrix matrix::operator -(){
    for(int i=0;i!=m_row;i++){
        for(int j=0;j!=m_col;j++){
            m_el[i][j] *= -1;
        };
    };
    return *this;
};

matrix matrix::operator+(matrix B){
    if(this->m_row != B.m_row || this->m_col != B.m_col){
        std::cout<<"Matrices cannot be added\n";
    }else{
        matrix sum = B;
        for(int i=0;i!=this->m_row;i++){
            for(int j=0;j!=this->m_col;j++){
                sum.m_el[i][j] = this->m_el[i][j] + B.m_el[i][j];
            };
        };
        return sum;
    };
    exit(0);
};

matrix matrix::operator-(matrix B){
    return *this + (-B);
};

matrix matrix::operator*(matrix B){
    if(this->m_col == B.m_row){
        matrix product(this->m_row,B.m_col);

        for(int i=0;i!=this->m_row;i++){
            for(int j=0;j!=B.m_col;j++){
                for(int k=0;k!=m_col;k++){
                    product.m_el[i][j] += (this->m_el[i][k]*B.m_el[k][j]);
                };
            };
        };
        return product;
    }else{
        std::cout<<"Matrices dimensions don't agree\n";
        exit(0);
    }
};

matrix& matrix::operator = (const matrix& other){
    if (this == &other) return *this;
        for (int i = 0; i < m_row; i++) delete[] m_el[i];
        delete[] m_el;

        m_row = other.m_row;
        m_col = other.m_col;
        m_el = new double*[m_row];
        for (int i = 0; i < m_row; i++) {
            m_el[i] = new double[m_col];
            std::copy(other.m_el[i], other.m_el[i] + m_col, m_el[i]);
        };
        return *this;
    };



std::ostream& operator<<(std::ostream &o, const matrix &A){
    for(int i=0;i!=A.m_row;i++){
        for(int j=0;j!=A.m_col;j++){
            o<< A.m_el[i][j] <<' ';
        };
       o<<"\n";
};
    return o;
};


void matrix::fill_matrix(double**a){
    a=new double *[m_row];
    std::cout<<"Give me the entries of the matrix, row by row,\n"
        <<"separated by space and press enter\n";
    for (int k=0;k<m_row;k++){
        a[k]=new double [m_col];
        std::cout<<"row "<<k+1<<" :";
        for(int l=0;l!=m_col;l++){
            std::cin>>a[k][l];
        };
    };
    m_el = a;
    m_filled = true;
    };

void matrix::fill_matrix(){
    // Setup random number generator
    std::random_device rd;
    std::mt19937 gen(rd());  // Mersenne Twister engine
    std::uniform_int_distribution<> distr(-2, 2);

    m_el = new double * [m_row];
    for(int k=0;k!=m_row;k++){
        m_el[k] = new double [m_col];
        for(int l=0;l!=m_col;l++){
            m_el[k][l] = distr(gen);
        };
    };
    //std::cout<<"Matrix correctly filled.\n";
    m_filled =  true;
    };

matrix matrix::transpose(){
    if(!m_filled){
        std::cout<<"You did not provide the elements of the matrix\n";
        exit(1);
    }else{
            matrix transpose(m_row,m_col);
            double **t_el = new double* [m_row];
            for(int k=0;k!=m_row;k++){
                t_el[k] = new double [m_col];
                for(int l=0;l!=m_col;l++){
                    t_el[k][l] = m_el[l][k];
                };
            };
            transpose.set_el(t_el);

            return transpose;
    };
};


/* This function returns an integer which is
** +n -> is the index of the row with most zeros
** -n -> is the (-index-1) of the col with most zeros
** Useful to speed up determinant
*/


int matrix::find_most_zeros(){
    int count_r[m_row] {}, count_c[m_col] {};
    for(int k=0;k!=m_row;k++){
        for(int l=0;l!=m_col;l++){
            if(m_el[k][l] == 0)
                count_r[k]+=1;
            if(m_el[l][k] == 0)
                count_c[k]++;
            }
    };

    int n_row = 0, n_col = 0;

    for(int k=0;k<m_row-1;k++){
       if(count_r[k+1]>=count_r[k]) n_row=k+1;
       if(count_c[k+1]>=count_c[k]) n_col=k+1;
    }

    if(count_r[n_row] == count_c[n_col]) return n_row;
    if(count_r[n_row] > count_c[n_col]) return n_row;
    if(count_r[n_row] < count_c[n_col]) return -n_col-1;

    return 0;
};

matrix matrix::swap_rows(int i, int j){
    if(i==j)
        return *this;
    else{
        double temp[m_col] {};
        for(int k=0;k!=m_col;k++){
            temp[k] = m_el[i][k];
            m_el[i][k] = m_el[j][k];
            m_el[j][k] = temp[k];
        };
        return *this;
    };
};

matrix matrix::sum_rows(int row1, int row2, double coeff){
    if(row1>m_row || row2>m_col) std::cout<<"ERROR.";

    for(int k=0;k!=m_col;k++){
        m_el[row2][k] += coeff*m_el[row1][k];
    };
    //std::cout<< *this<<std::endl;
    return *this;

};
