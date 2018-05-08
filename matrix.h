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
    public:
        template <typename T>
        friend std::istream &operator>> (std::istream &input, Matrix<T> &matrix);   //wczytanie z cin

		template <typename T>
		friend std::ostream &operator<< (std::ostream &output, Matrix<T> &matrix);   //wypisanie do cout

        void adapt(int y, int x)    //wypelnienie macierzy losowymi wartosciami
        {
            type save;
            int i,j;    //countery
            srand(time(NULL));  //seed
            for(j=0;j<y;j++)
            {
                for(i=0;i<x;i++)
                {
                    save=rand()/rand();    //dana losowa
                    this->at(j).push_back(save);    //zapisywanie
                }
                this->init();   //nowy wiersz
            }
        }

        template <typename T>
        Matrix<T> operator+ (Matrix<T> &matrix) //dodawanie
        {
            T save;
            Matrix<T> blank;    //na tym pracujemy
            if((this->size()!=matrix.size())||(this->at(0).size()!=matrix[0].size())) return blank; //jezeli zle wymiary
            int j,i;    //countery
            for(j=0;j<this->size()-1;j++)   //zewnetrzny wektor
            {
                for(i=1;i<this->at(0).size();i++)   //wewnetrzny wektor (na pozycji 0 zawsze sa 0)
                {
                    save=this->at(j).at(i)+matrix[j][i];
                    (blank[j]).push_back(save);   //zapisanie
                }
                blank.init();   //nowy wiersz
            }
            return blank;
        }

        template <typename T>
        Matrix<T> operator* (Matrix<T> &matrix) //mnozenie
        {
            T save;
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
                    save=sum;
                    (blank[j]).push_back(save);   //zapisujemy
                }
                blank.init();   //nowy wiersz
            }
            return blank;
        }

        template <typename T>
        Matrix<T> operator*= (Matrix<T> &matrix)    //analogicznie do *
        {
            T save;
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
                    save=sum;
                    (blank[j]).push_back(save);
                }
                blank.init();
            }
            *this=blank;
            return *this;
        }

        template <typename T>
        Matrix<T> operator- (Matrix<T> &matrix) //analogicznie do +
        {
            T save;
            Matrix<T> blank;
            if((this->size()!=matrix.size())||(this->at(0).size()!=matrix[0].size())) return blank;
            int j,i;
            for(j=0;j<this->size()-1;j++)
            {
                for(i=1;i<this->at(0).size();i++)
                {
                    save=this->at(j).at(i)-matrix[j][i];
                    (blank[j]).push_back(save);
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

        template <typename T>   //operator przypisania
        Matrix<T> operator=(Matrix<T> &matrix)
        {
            this->clear();  //czyscimy to co bylo
            this->init();   //robimy miejsce
            int i;  //counter
            for(i=0;i<matrix.size()-1;i++)
            {
                this->at(i)=matrix.at(i);   //przypisujemy
                this->init();   //robimy miejsce
            }
            return *this;
        }

        Matrix(void)    //konstruktor
        {
            std::vector<type> temp;
            temp.push_back(0);  //size zawsze wiekszy o 1 i wspolrzedne wektorow "wewnetrzych" zawsze przesuniete o 1
            this->push_back(temp);
            return;
        }

        template<size_t x, size_t y>    //rozmiary tablic
        Matrix(type (&arr)[x][y])   //konstruktor
        {
            int i,j;    //countery
            this->init();   //tworzymy miejsce
            for(j=0;j<x;j++)
            {
                for(i=0;i<y;i++)
                {
                    this->at(j).push_back(arr[j][i]);   //zapisujemy
                }
                this->init();   //tworzymy miejsce
            }
            return;
        }

        Matrix(Matrix<type> &matrix)    //konstruktor kopiujacy
        {
            this->init();   //tworzymy miejsce
            int i;  //counter
            for(i=0;i<matrix.size()-1;i++)
            {
                this->at(i)=matrix.at(i);   //przypisujemy vectory
                this->init();   //tworzymy miejsce
            }
            return;
        }

        ~Matrix(void)   //destruktor (u mnie dziala ale na szkolnym nie :( )
        {
            int i;
            for(i=0;i<this->size();i++) //niszczymy kazdy wektor wewnetrzny
            {
                this->at(i).clear();
            }
            this->clear();  //i zedwnetrzny
        }

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
    int crdy, flag, read;   //licznik wspolrzednej y, flaga, ilosc wczytanych rzeczy
    type save;  //sluzy do zapisywania danych
    crdy=read=flag=0;
    do
    {
        do
        {
            if((flag!=0)&&(read==flag)) //ktos chce za duzo wpisac
            {
                cout<<"cut"<<endl;
                fseek(stdin, 0, SEEK_END);  //obcinamy
                break;
            }
            input>>save;    //zapisujemy
            (matrix[crdy]).push_back(save);
            read++; //przeczytano
        }
        while(input.get()!='\n');	//jezeli enter, przechodzimy do nizszej kolumny
        while ((read!=flag)&&(flag!=0)) //za malo ktos wpisal
        {
            save=0;
            (matrix[crdy]).push_back(save); //zapisujemy 0
            read++;
        }
        crdy++; //nastepna wspolrzedna
        matrix.init();  //robimy miejsce
        flag=read;  //maksymalny wymiar
        read=0;
    }
    while(input.peek()!='\n');
    return input;
}

template <typename type>
ostream &operator<<(ostream &output, Matrix<type> &matrix)   //wypisanie do cout
{
    int i,j;    //countery
    for(j=0;j<matrix.size()-1;j++)
    {
        for(i=1;i<(matrix[0]).size();i++)
        {
            output<<matrix[j][i]<<' ';  //wypisanie
        }
        output<<endl;   //newline
    }
    return output;
}
#endif

