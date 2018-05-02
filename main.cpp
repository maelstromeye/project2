#include "matrix.h"
using namespace std;
template <typename type>
std::istream &operator>>(std::istream &input, type &matrix)   //wczytanie z cin
{
    return input;
}
template <typename type>
std::ostream &operator<<(std::ostream &output, type &matrix)   //wypisanie do cout
{
    return output;
}
int main()
{
    Matrix<int> mat1;
    cin>>mat1;
    cout<<mat1;

    return 0;
}
