#include "matrix.h"
#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
template <typename type>
istream &operator>>(istream &input, type &matrix)   //wczytanie z cin
{
    char space;
    int crdy, flag, read;
    crdy=read=flag=0;
    do
    {
        do
        {
            if((flag!=0)&&(read==flag))
            {
                cout<<"cut"<<endl;
                fseek(stdin, 0, SEEK_END);
                break;
            }
            input>>matrix.save;
            (matrix[crdy]).push_back(matrix.save);
            read++;
        }
        while(input.get()!='\n');	//jezeli enter, przechodzimy do nizszej kolumny
        while ((read!=flag)&&(flag!=0))
        {
            matrix.save=0;
            (matrix[crdy]).push_back(matrix.save);
            read++;
        }
        crdy++;
        matrix.init();
        flag=read;
        read=0;
    }
    while(input.peek()!='\n');
    return input;
}

template <typename type>
ostream &operator<<(ostream &output, Matrix<type> &matrix)   //wypisanie do cout
{
    int i,j;
    for(j=0;j<matrix.size()-1;j++)
    {
        for(i=1;i<(matrix[0]).size();i++)
        {
            output<<matrix[j][i]<<' ';
        }
        output<<endl;
    }
    return output;
}

int main()
{
    Matrix<int> mat1, mat2;
    cin>>mat1;
    cout<<mat1<<endl;
    cin>>mat2;
    cout<<mat2<<endl;
    mat1*=mat2;
    cout<<mat1;
    return 0;
}
