#ifndef DEF
#define DEF
#include<iostream>
#include<vector>
template <typename type>
std::istream &operator>>(std::istream &input, type &matrix);   //wczytanie z cin
template <typename type>
class Matrix : public std::vector<std::vector<type> >
{
    private:
        type save;
    public:
        friend std::istream &operator>> <>(std::istream &input, Matrix<type> &matrix);   //wczytanie z cin

		template <typename T>
		friend std::ostream &operator<< (std::ostream &output, Matrix<T> &matrix);   //wypisanie do cout

        template <typename T>
        Matrix<T> operator+ (Matrix<T> &matrix)
        {
            Matrix<T> blank;
            if((this->size()!=matrix.size())||(this->at(0).size()!=matrix[0].size())) return blank;
            int j,i;
            for(j=0;j<this->size()-1;j++)
            {
                for(i=1;i<this->at(0).size();i++)
                {
                    blank.save=this->at(j).at(i)+matrix[j][i];
                    (blank[j]).push_back(blank.save);
                }
                blank.init();
            }
            return blank;
        }

        template <typename T>
        Matrix<T> operator* (Matrix<T> &matrix)
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
            return blank;
        }

        template <typename T>
        Matrix<T> operator*= (Matrix<T> &matrix)
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
        Matrix<T> operator- (Matrix<T> &matrix)
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
        Matrix<T> operator+= (Matrix<T> &matrix)
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
        Matrix<T> operator-= (Matrix<T> &matrix)
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
        bool operator== (Matrix<T> &matrix)
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
        bool operator!= (Matrix<T> &matrix)
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

        Matrix(void)
        {
            std::vector<type> temp;
            temp.push_back(0);
            this->push_back(temp);
            return;
        }

        ~Matrix(void)
        {
            int i;
            for(i=0;i<this->size();i++)
            {
                this->at(i).~vector();
            }
            this->clear();
        }

        void init(void)
        {
            std::vector<type> temp;
            temp.push_back(0);
            this->push_back(temp);
            return;
        }

        type reveal(int x, int y)
        {
            x++;
            if (x+1>((this->at(0)).size())) return 0;
            if (y+1>(this->size())-1) return 0;
            return (this->at(y)).at(x);
        }

        bool change(int x, int y, type numb)
        {
            x++;
            if (x+1>((this->at(0)).size())) return false;
            if (y+1>(this->size())-1) return false;
            (this->at(y)).at(x)=numb;
            return true;
        }
};


#endif

