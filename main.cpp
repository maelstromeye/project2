#include "matrix.h"
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
template <typename type>
bool general_test(void);
template <typename type>
void adapt(Matrix<type> &matrix, int y, int x);
int change(void);
int next(int x);
int main()
{
    int arr[3][3] {{2,3,4},{2,4,6},{7,3,1}};
    Matrix<int> mat(arr);
    cout<<mat;
    Matrix<int> mat2(mat);
    cout<<mat2;
    string command;
    while(1)
    {
        cout<<"Welcome! Choose what you want to do."<<endl;
        cout<<"-'test' to run a general test of random matrices of specified type"<<endl;
        cout<<"-'kill' to end"<<endl;
        cin>>command;
        if (command=="test")
        {
            switch(change())
            {
                case 1:
                    if(general_test<double>()) cout<<"test pass"<<endl;
                    else cout<<"test fail"<<endl;
                    break;
                case 2:
                    if(general_test<complex<int> >()) cout<<"test pass"<<endl;
                    else cout<<"test fail"<<endl;
                    break;
                case 3:
                    if(general_test<int>()) cout<<"test pass"<<endl;
                    else cout<<"test fail"<<endl;
                    break;
                case 4:
                    if(general_test<complex<double> >()) cout<<"test pass"<<endl;
                    else cout<<"test fail"<<endl;
                    break;
                default:
                    break;
            }
        }
        else if(command=="kill") return 0;
        else cout<<"Unknown command"<<endl;
    }
    return 0;
}
template <typename type>
bool general_test(void)
{
    int i,j;
    Matrix<type> matrices[4];
    type n;
    cout<<"Construction...ok"<<endl;
    cout<<"Please input a matrix"<<endl;
    cin>>matrices[0];
    cout<<"Input...ok"<<endl;
    cout<<matrices[0]<<endl<<"Output...ok"<<endl<<"Randomizing matrix 2 with "<<matrices[0].size()-1<<"x"<<matrices[0][0].size()-1<<" dimensions"<<endl;
    matrices[1].adapt(matrices[0].size()-1, matrices[0][0].size()-1);
    cout<<matrices[1];
    cout<<"Comparing 2 matrices"<<endl;
    if (matrices[0]!=matrices[0]) {cout<<"Comparison fail... Aborting..."<<endl; return false;}
    if (!(matrices[0]==matrices[0])) {cout<<"Comparison fail... Aborting..."<<endl; return false;}
    if (matrices[0]==matrices[1]) cout<<"Matrices equal, comparison ok"<<endl;
    else cout<<"Matrices not equal, comparison ok"<<endl;
    cout<<"Adding both matrices"<<endl;
    matrices[2]=matrices[0]+matrices[1];
    cout<<matrices[2];
    cout<<"Adding with assignment"<<endl;
    matrices[0]+=matrices[1];
    cout<<matrices[0];
    if (matrices[0]==matrices[2]) cout<<"Simple maths...ok"<<endl;
    else {cout<<"Simple maths fail... Aborting..."<<endl; return false;}
    cout<<"Generating random matrix multipliable by the one above..."<<endl;
    matrices[3].adapt(matrices[0][0].size()-1, matrices[0].size()-1);
    cout<<matrices[3];
    cout<<"Multiplying matrices..."<<endl;
    matrices[2]=matrices[0]*matrices[3];
    cout<<matrices[2];
    cout<<"Multiplying with assignment..."<<endl;
    matrices[0]*=matrices[3];
    cout<<matrices[0];
    if (matrices[0]==matrices[2]) cout<<"Multiplication...ok"<<endl;
    else {cout<<"Multiplication fail... Aborting..."<<endl; return false;}
    cout<<"Testing accessing and changing elements... Access element of matrix 1:"<<endl;
    cout<<matrices[0];
    i=rand()%(matrices[0][0].size()-1);
    j=rand()%(matrices[0].size()-1);
    cout<<"At:("<<j<<","<<i<<")"<<endl<<matrices[0].reveal(i,j)<<endl;
    if(matrices[0].reveal(i,j)!=matrices[0].at(j).at(i+1)) {cout<<"Access fail... Aborting..."<<endl; return false;}
    else cout<<"Access...ok"<<endl;
    n=rand()/rand();
    cout<<"Changing element at ("<<j<<","<<i<<") of matrix 1 to: "<<n<<endl;
    matrices[0].change(i,j,n);
    cout<<"Matrix 1 is now:"<<endl;
    cout<<matrices[0];
    if (matrices[0].reveal(i,j)!=n) {cout<<"Element change fail... Aborting..."<<endl; return false;}
    else cout<<"Element change...ok"<<endl;
    cout<<"All matrix functions operational"<<endl;
    return true;
}
int change(void)
{
    string command;
    cout<<"Specify the type (int, double, complexint, complexdouble)"<<endl;
    cin>>command;
    if (command=="double") return 1;
    else if (command=="complexint") return 2;
    else if (command=="int") return 3;
    else if (command=="complexdouble") return 4;
    else
    {
        cout<<"Unknown type, assuming int"<<endl;
    }
    return 3;
}

