#ifndef DEF
#define DEF
#include<iostream>
#include<vector>
template <typename type>
std::istream &operator>>(std::istream &input, type &matrix);   //wczytanie z cin
template <typename type>
std::ostream &operator<<(std::ostream &output, type &matrix);
template <typename type>
class Matrix : public std::vector<std::vector<type> >
{
    private:
        type i;
    public:
        friend std::istream &operator>> <>(std::istream &input, Matrix<type> &matrix);   //wczytanie z cin
		friend std::ostream &operator<< <>(std::ostream &output, Matrix<type> &matrix);   //wypisanie do cout

};

#endif
