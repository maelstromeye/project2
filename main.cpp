#include "matrix.h"
#include <cctype>
#include <cstdio>
#include <iostream>
using namespace std;
template <typename type>
istream &operator>>(istream &input, type &matrix)   //wczytanie z cin
{
    char space;
    int crdy;
    crdy=0;
    do
    {
        do
        {
            input>>matrix.save;
            (matrix[crdy]).push_back(matrix.save);
        }
        while(input.get()!='\n');	//jezeli enter, przechodzimy do nizszej kolumny
        crdy++;
        matrix.init();
        cout<<matrix.size()<<endl;
    }
    while(input.peek()!='\n');
    return input;
}

template <typename type>
ostream &operator<<(ostream &output, type &matrix)   //wypisanie do cout
{
    int i,j;
    for(j=0;j+1<matrix.size();j++)
    {
        for(i=1;i<(matrix[0]).size();i++)
        {
            cout<<matrix[j][i]<<' ';
        }
        cout<<endl;
    }
    return output;
}

int main()
{
    Matrix<int> mat1;
    cin>>mat1;
    cout<<mat1;

    return 0;
}
