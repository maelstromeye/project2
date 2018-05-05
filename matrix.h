#ifndef DEF
#define DEF
#include <iostream>
#include <cstdio>
#include <vector>
#include <complex>
#include <cstdlib>
#include <ctime>
template <typename type>
class Matrix : public std::vector<std::vector<type> >   //dziedziczenie z std::vector
{
    private:
        type save;  //potrzebne do zapisywania
    public:
        template <typename T>
        friend std::istream &operator>> (std::istream &input, Matrix<T> &matrix);   //wczytanie z cin

		template <typename T>
		friend std::ostream &operator<< (std::ostream &output, Matrix<T> &matrix);   //wypisanie do cout

        void adapt(int y, int x)
        {
            int i,j;
            srand(time(NULL));
            for(j=0;j<y;j++)
            {
                for(i=0;i<x;i++)
                {
                    this->save=rand()/rand();
                    this->at(j).push_back(this->save);
                }
                this->init();
            }
        }

        template <typename T>
        Matrix<T> operator+ (Matrix<T> &matrix) //dodawanie
        {
            Matrix<T> blank;    //na tym pracujemy
            if((this->size()!=matrix.size())||(this->at(0).size()!=matrix[0].size())) return blank; //jezeli zle wymiary
            int j,i;    //countery
            for(j=0;j<this->size()-1;j++)   //zewnetrzny wektor
            {
                for(i=1;i<this->at(0).size();i++)   //wewnetrzny wektor (na pozycji 0 zawsze sa 0)
                {
                    blank.save=this->at(j).at(i)+matrix[j][i];
                    (blank[j]).push_back(blank.save);   //zapisanie
                }
                blank.init();   //nowy wiersz
            }
            return blank;
        }

        template <typename T>
        Matrix<T> operator* (Matrix<T> &matrix) //mnozenie
        {
            Matrix<T> blank;    //na tym pracujemy
            if((this->at(0).size()!=matrix.size())) return blank;   //zle wymiary
            int j,i,n;  //countery
            T sum;  //suma mnozenia wektor*wektor
            for(j=0;j<this->size()-1;j++)   //zewmnetrzny wektor
            {
                for(i=1;i<matrix.at(0).size();i++)  //wewnetrzny wektor
                {
                    for(n=1, sum=0;n<this->at(0).size();n++)    //mnozenie
                    {
                        sum+=matrix[n-1][i]*this->at(j).at(n);  //to zapiszemy
                    }
                    blank.save=sum;
                    (blank[j]).push_back(blank.save);   //zapisujemy
                }
                blank.init();   //nowy wiersz
            }
            return blank;
        }

        template <typename T>
        Matrix<T> operator*= (Matrix<T> &matrix)    //analogicznie do *
        {
            Matrix<T> blank;
            if((this->at(0).size()!=matrix.size())) return blank;
            int j,i,n;
            T sum;
            for(j=0;j<this->size()-1;j++)
            {
                for(i=1;i<matrix.at(0).size();i++)
                {
                    for(n=1, sum=0;n<this->at(0).size();n++)
                    {
                        sum+=matrix[n-1][i]*this->at(j).at(n);
                    }
                    blank.save=sum;
                    (blank[j]).push_back(blank.save);
                }
                blank.init();
            }
            *this=blank;
            return *this;
        }

        template <typename T>
        Matrix<T> operator- (Matrix<T> &matrix) //analogicznie do +
        {
            Matrix<T> blank;
            if((this->size()!=matrix.size())||(this->at(0).size()!=matrix[0].size())) return blank;
            int j,i;
            for(j=0;j<this->size()-1;j++)
            {
                for(i=1;i<this->at(0).size();i++)
                {
                    blank.save=this->at(j).at(i)-matrix[j][i];
                    (blank[j]).push_back(blank.save);
                }
                blank.init();
            }
            return blank;
        }

        template <typename T>
        Matrix<T> operator+= (Matrix<T> &matrix)    //analogicznie do +
        {
            Matrix<T> blank;
            if((this->size()!=matrix.size())||(this->at(0).size()!=matrix[0].size())) return blank;
            int j,i;
            for(j=0;j<this->size()-1;j++)
            {
                for(i=1;i<this->at(0).size();i++)
                {
                    this->at(j).at(i)+=matrix[j][i];
                }
            }
            return *this;
        }

        template <typename T>
        Matrix<T> operator-= (Matrix<T> &matrix) //analogicznie do -
        {
            Matrix<T> blank;
            if((this->size()!=matrix.size())||(this->at(0).size()!=matrix[0].size())) return blank;
            int j,i;
            for(j=0;j<this->size()-1;j++)
            {
                for(i=1;i<this->at(0).size();i++)
                {
                    this->at(j).at(i)-=matrix[j][i];
                }
            }
            return blank;
        }

        template <typename T>
        bool operator== (Matrix<T> &matrix) //analogicznie do +, tylko sprawdzenie rownosci zamiast dzialania i zwracanie false/true
        {
            if((this->size()!=matrix.size())||(this->at(0).size()!=matrix[0].size())) return false;
            int j,i;
            for(j=0;j<this->size()-1;j++)
            {
                for(i=1;i<this->at(0).size();i++)
                {
                    if (this->at(j).at(i)!=matrix[j][i]) return false;
                }
            }
            return true;
        }

        template <typename T>
        bool operator!= (Matrix<T> &matrix) //analogicznie do ==
        {
            if((this->size()!=matrix.size())||(this->at(0).size()!=matrix[0].size())) return true;
            int j,i;
            for(j=0;j<this->size()-1;j++)
            {
                for(i=1;i<this->at(0).size();i++)
                {
                    if (this->at(j).at(i)!=matrix[j][i]) return true;
                }
            }
            return false;
        }

        Matrix(void)    //konstruktor
        {
            std::vector<type> temp;
            temp.push_back(0);  //size zawsze wiekszy o 1 i wspolrzedne wektorow "wewnetrzych" zawsze przesuniete o 1
            this->push_back(temp);
            return;
        }

        /*~Matrix(void)   //destruktor (u mnie dziala ale na szkolnym nie :( )
        {
            int i;
            for(i=0;i<this->size();i++) //niszczymy kazdy wektor wewnetrzny
            {
                this->at(i).~vector();
            }
            this->clear();  //i zedwnetrzny
        }*/

        void init(void) //utworzenie nowego wiersza (z jakiegos powodu callowanie konstruktora nie dzialalo)
        {
            std::vector<type> temp;
            temp.push_back(0);
            this->push_back(temp);
            return;
        }

        type reveal(int x, int y)   //odkrycie elementu na danych wspolrzednych
        {
            x++;
            if (x+1>((this->at(0)).size())) return 0;   //poza zasiegiem
            if (y+1>(this->size())-1) return 0;
            return (this->at(y)).at(x);
        }

        bool change(int x, int y, type numb)    //zmiana wartosci elementu, analogicznie do reveal
        {
            x++;
            if (x+1>((this->at(0)).size())) return false;
            if (y+1>(this->size())-1) return false;
            (this->at(y)).at(x)=numb;
            return true;
        }
};
using namespace std;
template <typename type>
istream &operator>>(istream &input, Matrix<type> &matrix)   //wczytanie z cin
{
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
#endif

