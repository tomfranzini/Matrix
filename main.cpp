#include <iostream>
#include<cstdlib>

#include "matrices.h"

void mathematica_print_matrix(matrix& A){
    std::cout<<"{";
    for(int i=0;i!=A.get_row();i++){
        std::cout<<"{";
        for(int j=0;j!=A.get_col();j++){
            std::cout<<A.get_el()[i][j];
            if(j!=A.get_col()-1)
                std::cout<<',';
        };
        std::cout<<'}';
         if(i!=A.get_row()-1)
                std::cout<<',';
    };
    std::cout<<'}';
};

//Gauss algorithm to upper triangularise
matrix g_reduce(matrix A, int& swap){
    matrix gauss = A;
    int count;
    bool is_linearly_ind {true};

    for(int k=0;k!=gauss.get_row()-1;k++){
        count = k+1;
        while(gauss.get_el()[k][k] == 0 && count<gauss.get_row()){
            gauss.swap_rows(k,count);
            swap+=1;
            //std::cout<<"I swapped because I found a zero and I now have\n"<<tri<<std::endl;
            count++;
        };

        if(count == gauss.get_row()){
            is_linearly_ind = false; //In this case determinant is zero
        }
        else{
            for(int l=k+1;l!=gauss.get_row();l++){
                double coefficient = -gauss.get_el()[l][k]/gauss.get_el()[k][k];
                gauss.sum_rows(k,l,coefficient);
            };
        };;
    };

//At this point the matrix is upper triangular
if(gauss.get_el()[gauss.get_row()-1][gauss.get_row()-1] != 0){
    for(int k=gauss.get_row()-1;k!=0;k--){
            for(int l=k-1;l!=-1;l--){
                if(gauss.get_el()[k][k]!=0){
                double coefficient = -gauss.get_el()[l][k]/gauss.get_el()[k][k];
                gauss.sum_rows(k,l,coefficient);
                };
            };
        };
}else{
    throw std::runtime_error("Matrix rows are linearly dependent.");
    return gauss;
};
return gauss;
};






//Need to implement a LOWER triengular, in order to INVERT the matrix


double determinant(matrix A){
    matrix diag, temp = A;
    int swap = 0;
    try{
         diag = g_reduce(temp,swap);
    } catch (const std::runtime_error& err) {
        std::cerr << "Determinant cannot be computed. " << err.what() << '\n';
        return 0;
    }

    double determinant = (swap%2 == 0) ? 1 : -1;
    for(int i=0;i!=diag.get_row();i++){
        determinant *= diag.get_el()[i][i];
    };
    return determinant;
};



////////////////////////////////////////////
////////////////////////////////////////////


int main(){

    int row,col;
    int choice1, choice2;
    double **elements;
    bool prompt {false};
    std::cout<<"\n::::::::::::::::::::::::::::::::::::::::::\n";
    std::cout<<"::::::::::::::MATRIX FACTORY::::::::::::::\n";
    std::cout<<"::::::::::::::::::::::::::::::::::::::::::\n";


    while(true){

    do{
    std::cout<<"\nTell me the dimension of the matrix:\n";
    std::cout<<"rows: ", std::cin>>row;
    std::cout<<"columns: ", std::cin>>col;
    }while((row>10 || row<=0) || (col>10 || col<=0));

    matrix M(row,col);

    std::cout<<"\nHow do you want to fill in the matrix?\n";
    std::cout
        <<"1: Manually\n"
        <<"2: Randomly.\n"
        <<"3: Exit\n";
    do{
        std::cin>>choice1;
        if(choice1<1 || choice1>3){
            std::cout<<"Improper command, retry\n";
        }else
            prompt=true;
    }while(!prompt);
    
    switch(choice1){
        case 1: M.matrix::fill_matrix(elements);break;
            ;
        case 2: M.matrix::fill_matrix(); break;
            ;
        case 3:
            std::cout<<"Exiting the program.\n";
            exit(1);
    };

    std::cout<<"\nMatrix correctly filled.\n";
    std::cout<<"Your matrix is ";
    mathematica_print_matrix(M);
    std::cout<<std::endl;

        while(true){
    std::cout<<"\n**************************************\n";
    std::cout<<"\nNow what do you want to do with it?\n";
    std::cout
        <<"0: Use a new matrix\n"
        <<"1: Diagonalise.\n"
        <<"2: Compute the determinant.\n"
        <<"3: Compute the inverse\n"
        <<"4: Study the associated linear system\n"
        <<"5: Exit.\n";

    do{
        std::cin>>choice2;
        if(choice2<0 || choice2>5){
            std::cout<<"Improper command, retry\n";
        }else
            prompt=true;
    }while(!prompt);

    switch(choice2){
        case 0: break;
        case 1:
            std::cout<<"\nApplying Gauss algorithm. The diagonal matrix is:\n";
            try{
                std::cout<<g_reduce(M,choice1); [[fallthrough]];
            } catch (const std::runtime_error& err) {
                std::cerr << "The matrix is\n"<<g_reduce(M,choice1)<<"and it looks singular. " << err.what() << '\n';
                break;
            };
            break;

        case 2:
            try{

                std::cout<<"\nThe determinant of the matrix is "<<determinant(M)<<std::endl; [[fallthrough]];
            } catch (const std::runtime_error& err) {
                std::cerr << "The determinant is zero. " << err.what() << '\n';
            };

            std::cout<<"To check in Mathematica, you can use the following command: Det[";
            mathematica_print_matrix(M);
            std::cout<<']'<<std::endl;
            break;
        case 3:
            std::cout<<"\nNot ready yet..."<<std::endl;
            break;
        case 4:
            std::cout<<"\nNot ready yet..."<<std::endl;
            break;
        case 5:
            std::cout<<"Exiting the program.\n";
            exit(1);
    };
    if(choice2==0) break;
    };

    };

}
