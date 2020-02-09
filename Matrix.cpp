#include <iostream>
#include <stdexcept>
using namespace std;

class Complex;
class Matrix;
class Rectangular_Matrix;
class Square_Matrix;

class Complex
{
    friend class Square_Matrix;
    double r;
    double i;

public:
    Complex()
    {
        this->r = 0;
        this->i = 0;
    }
    Complex(int x , int y)
    {
        this->r = x;
        this->i = y;
    }
    ~Complex() = default;
    bool is_zero()
    {
        return(this->r == 0 && this->i == 0);
    };
    double modulus()
    {
        return (this->r * this->r + this->i * this->i);
    }

    Complex& operator= ( Complex const& a)
    {
        this->r = a.r;
        this->i = a.i;
        return *this;
    }
    bool operator == (const Complex& a)
    {
        return(this->r == a.r && this->i == a.i);
    }
    bool operator != (const Complex& a)
    {
        return(!(*this == a));
    }
    bool operator < (const Complex& a)
    {
        if (a.r != this->r) return (this->r < a.r);
        return (this->i < a.i);
    }

    Complex operator+ (const Complex& a)
    {
        Complex b;
        b.r = a.r + r;
        b.i = a.i + i;
        return b;
    }
    Complex operator- (const Complex& a)
    {
        Complex b;
        b.r = a.r - r;
        b.i = a.i - i;
        return b;
    }

    Complex operator~ ()
    {
        Complex a;
        a.r = r;
        a.i = -i;
        return a;
    }

    Complex operator* (const Complex& a)
    {
        Complex b;
        b.r = a.r * r - a.i * i;
        b.i = a.r * i + a.i * r;
        return b;
    }
    Complex operator* (double n)
    {
        Complex a;
        a.r = n * r;
        a.i = n * i;
        return a;
    }
    Complex operator/ (const Complex& a)
    {
        if(a.r == 0 && a.i == 0)
            throw invalid_argument("Can't divide by 0");
        Complex c;
        c.r = (a.r * this->r + a.i * this->i) / (a.r * a.r + a.i * a.i);
        c.i = (a.r * this->i - a.i * this->r) / (a.r * a.r + a.i * a.i);
        return c;
    }
    Complex operator/ (double n)
    {
        if(n == 0)
            throw invalid_argument("Can't divide by 0");
        Complex a;
        a.r = r / n;
        a.i = i / n;
        return a;
    }

    friend Rectangular_Matrix operator *(const Rectangular_Matrix& A , const Rectangular_Matrix& B);
    friend Rectangular_Matrix operator *(const Square_Matrix& A , const Rectangular_Matrix& B);
    friend Rectangular_Matrix operator *(const Rectangular_Matrix& A , const Square_Matrix& B);

    friend istream& operator >> (std::istream& in, Complex& a);
    friend ostream& operator << (std::ostream& out, Complex& a);
};

class Matrix
{
    friend class Rectangular_Matrix;
    friend class Square_Matrix;
    Complex **M;

public:
    Matrix(int x , int y)
    {
        M = new Complex*[x];
        for(int i=0 ; i<x ; i++)
            M[i] = new Complex[y];
    }
    ~Matrix()
    {
        //cout<<"M deleted"<<"\n";
    }

    friend Rectangular_Matrix operator *(const Rectangular_Matrix& A , const Rectangular_Matrix& B);
    friend Rectangular_Matrix operator *(const Square_Matrix& A , const Rectangular_Matrix& B);
    friend Rectangular_Matrix operator *(const Rectangular_Matrix& A , const Square_Matrix& B);

    friend istream& operator >> (std::istream& in, Rectangular_Matrix& a);
    friend ostream& operator << (std::ostream& out, Rectangular_Matrix& a);
    friend istream& operator >> (std::istream& in, Square_Matrix& a);
    friend ostream& operator << (std::ostream& out, Square_Matrix& a);

    virtual bool is_superior() = 0;
    virtual bool is_inferior() = 0;
    virtual bool is_diagonal() = 0;
};

class Rectangular_Matrix : public Matrix
{
    int lin , col;

public:
    Rectangular_Matrix(int x , int y): Matrix(x , y)
    {
        lin = x;
        col = y;
    }
    ~Rectangular_Matrix()
    {
        for(int i=0 ; i<lin ; i++)
            delete [] M[i];
        delete [] M;
        lin = 0;
        col = 0;
    }

    Rectangular_Matrix& operator= ( Rectangular_Matrix const& a)
    {
        for(int i=0 ; i<this->lin ; i++)
            delete [] this->M[i];
        delete [] this->M;
        this->lin = a.lin;
        this->col = a.col;
        this->M = new Complex*[a.lin];
        for(int i=0 ; i<a.lin ; i++)
            this->M[i] = new Complex[a.col];
        for(int i=0 ; i<a.lin ; i++)
            for (int j=0 ; j<a.col ; j++)
                this->M[i][j] = a.M[i][j];
        return *this;
    }
    bool operator == (const Rectangular_Matrix& a)
    {
        if(this->lin != a.lin || this->col == a.col)
            return false;
        for(int i=0 ; i<a.lin ; i++)
            for (int j=0 ; j<a.col ; j++)
                if(this->M[i][j] != a.M[i][j])
                    return false;
        return true;
    }
    bool operator != (const Rectangular_Matrix& a)
    {
        return(!(*this == a));
    }

    Rectangular_Matrix operator +(const Rectangular_Matrix& a)
    {
        if(a.lin != this->lin || a.col != this->col)
            throw invalid_argument("Rectangular Matrices to be added have different size");
        Rectangular_Matrix b(this->lin , this->col);
        for(int i=0 ; i<a.lin ; i++)
            for(int j=0 ; j<a.col; j++)
                b.M[i][j] = a.M[i][j] + this->M[i][j];
        return b;
    }
    Rectangular_Matrix operator -(const Rectangular_Matrix& a)
    {
        if(a.lin != this->lin || a.col != this->col)
            throw invalid_argument("Rectangular Matrices to be added have different size");
        Rectangular_Matrix b(this->lin , this->col);
        for(int i=0 ; i<a.lin ; i++)
            for(int j=0 ; j<a.col; j++)
                b.M[i][j] = a.M[i][j] - this->M[i][j];
        return b;
    }

    friend Rectangular_Matrix operator *(const Rectangular_Matrix& A , const Rectangular_Matrix& B);
    friend Rectangular_Matrix operator *(const Square_Matrix& A , const Rectangular_Matrix& B);
    friend Rectangular_Matrix operator *(const Rectangular_Matrix& A , const Square_Matrix& B);

    friend istream& operator >> (std::istream& in, Rectangular_Matrix& a);
    friend ostream& operator << (std::ostream& out, Rectangular_Matrix& a);

    bool is_superior() override
    {
        return false;
    }
    bool is_inferior() override
    {
        return false;
    }
    bool is_diagonal() override
    {
        return false;
    }
};

class Square_Matrix : public Matrix
{
    int dim;

public:
    Square_Matrix(int x): Matrix(x , x)
    {
        dim = x;
        //det = 0;
    }
    ~Square_Matrix()
    {
        for(int i=0 ; i<dim ; i++)
            delete [] M[i];
        delete [] M;
        dim = 0;
    }

    Square_Matrix& operator= ( Square_Matrix const& a)
    {
        for(int i=0 ; i<this->dim ; i++)
            delete [] this->M[i];
        delete [] this->M;
        this->dim = a.dim;
        this->M = new Complex*[a.dim];
        for(int i=0 ; i<a.dim ; i++)
            this->M[i] = new Complex[a.dim];
        for(int i=0 ; i<a.dim ; i++)
            for (int j=0 ; j<a.dim ; j++)
                this->M[i][j] = a.M[i][j];
        return *this;
    }
    bool operator == (const Square_Matrix& a)
    {
        if(this->dim != a.dim || this->dim == a.dim)
            return false;
        for(int i=0 ; i<a.dim ; i++)
            for (int j=0 ; j<a.dim ; j++)
                if(this->M[i][j] != a.M[i][j])
                    return false;
        return true;
    }
    bool operator != (const Square_Matrix& a)
    {
        return(!(*this == a));
    }

    Square_Matrix operator +(const Square_Matrix& a)
    {
        if(a.dim != this->dim)
            throw invalid_argument("Square Matrices to be added have different size");
        Square_Matrix b(a.dim);
        for(int i=0 ; i<a.dim ; i++)
            for(int j=0 ; j<a.dim; j++)
                b.M[i][j] = a.M[i][j] + this->M[i][j];
        return b;
    }
    Square_Matrix operator -(const Square_Matrix& a)
    {
        if(a.dim != this->dim)
            throw invalid_argument("Square Matrices to be added have different size");
        Square_Matrix b(a.dim);
        for(int i=0 ; i<a.dim ; i++)
            for(int j=0 ; j<a.dim; j++)
                b.M[i][j] = a.M[i][j] - this->M[i][j];
        return b;
    }
    Square_Matrix operator *(const Square_Matrix& A)
    {
        if(A.dim != this->dim)
            throw invalid_argument("Square Matrices to be multiplied have different size");
        Square_Matrix B(A.dim);
        for(int i=0 ; i<A.dim ; i++)
            for(int j=0 ; j<A.dim ; j++)
            {
                B.M[i][j].r = 0;
                B.M[i][j].i = 0;
                for(int l=0 ; l<A.dim ; l++)
                    B.M[i][j] = B.M[i][j] + A.M[l][j]*this->M[i][l];
            }
        return B;
    }

    friend Rectangular_Matrix operator *(const Square_Matrix& A , const Rectangular_Matrix& B);
    friend Rectangular_Matrix operator *(const Rectangular_Matrix& A , const Square_Matrix& B);

    bool is_superior() override
    {
        for(int i=1 ; i<dim ; i++)
            for( int j=i+1 ; j<dim ; j++)
                if(!this->M[i][j].is_zero())
                    return false;
        return true;
    }
    bool is_inferior() override
    {
        for(int i=0 ; i<dim-1 ; i++)
            for( int j=i+1 ; j<dim ; j++)
                if(!this->M[i][j].is_zero())
                    return false;
        return true;
    }
    bool is_diagonal() override
    {
        return(this->is_inferior() && this->is_superior());
    }

    Square_Matrix transpose()
    {
        Square_Matrix T(this->dim);
        for(int i=0 ; i<this->dim ; i++)
            for(int j=0 ; j<this->dim ; j++)
            {
                T.M[i][j] = this->M[j][i];
            }
        return T;
    }
    Square_Matrix get_minor (int p  , int q)
    {
        Square_Matrix temp(this->dim - 1);
        int i = 0, j = 0;
        for (int row=0 ; row<this->dim ; row++)
        {
            for (int col=0 ; col<this->dim ; col++)
            {
                if (row != p && col != q)
                {
                    temp.M[i][j++] = this->M[row][col];
                    if (j == this->dim - 1)
                    {
                        j = 0;
                        i++;
                    }
                }
            }
        }
        return temp;
    }
    Complex det()
    {
        Complex D;

        if (this->dim == 1)
            return this->M[0][0];

        int sign = 1;
        for (int f = 0; f < this->dim; f++)
        {
            Square_Matrix temp(this->dim);
            temp = *this;
            temp = temp.get_minor(0, f);
            D = D + this->M[0][f] * temp.det() * sign;
            sign = -sign;
        }

        return D;
    }
    Square_Matrix inverse()
    {
        if(this->det().r == 0 && this->det().i == 0)
            throw invalid_argument("Matrix doesn't have an inverse");
        Square_Matrix I(this->dim);
        Complex e(1,0) , d = e / this->det();
        for(int i=0 ; i<this->dim ; i++)
            for(int j=0 ; j<this->dim ; j++)
            {
                I.M[i][j] = d * this->get_minor(j , i).det() * (-((i+j)%2)*2+1);
            }
        return I;
    }
    friend istream& operator >> (std::istream& in, Square_Matrix& a);
    friend ostream& operator << (std::ostream& out, Square_Matrix& a);
};

Rectangular_Matrix operator *(const Rectangular_Matrix& A , const Rectangular_Matrix& B)
{
    if(A.col != B.lin)
        throw invalid_argument("Square Matrices to be multiplied have different size");
    Rectangular_Matrix C(A.lin , B.col);
    for(int i=0 ; i<A.lin ; i++)
        for(int j=0 ; j<B.col ; j++)
        {
            C.M[i][j].r = 0;
            C.M[i][j].i = 0;
            for(int l=0 ; l<A.col ; l++)
                C.M[i][j] = C.M[i][j] + A.M[i][l]*B.M[l][j];
        }
    return C;
}
Rectangular_Matrix operator *(const Square_Matrix& A , const Rectangular_Matrix& B)
{
    if(A.dim != B.lin)
        throw invalid_argument("Square Matrices to be multiplied have different size");
    Rectangular_Matrix C(A.dim , B.col);
    for(int i=0 ; i<A.dim ; i++)
        for(int j=0 ; j<B.col ; j++)
        {
            C.M[i][j].r = 0;
            C.M[i][j].i = 0;
            for(int l=0 ; l<A.dim ; l++)
                C.M[i][j] = C.M[i][j] + A.M[i][l]*B.M[l][j];
        }
    return C;
}
Rectangular_Matrix operator *(const Rectangular_Matrix& A , const Square_Matrix& B)
{
    if(A.col != B.dim)
        throw invalid_argument("Square Matrices to be multiplied have different size");
    Rectangular_Matrix C(A.col , B.dim);
    for(int i=0 ; i<A.col ; i++)
        for(int j=0 ; j<B.dim ; j++)
        {
            C.M[i][j].r = 0;
            C.M[i][j].i = 0;
            for(int l=0 ; l<A.col ; l++)
                C.M[i][j] = C.M[i][j] + A.M[i][l]*B.M[l][j];
        }
    return C;
}

istream& operator >> (std::istream& in, Complex& a)
{
    in >> a.r;
    in >> a.i;
    return in;
}
ostream& operator << (std::ostream& out, Complex& a)
{
    if(a.i == 0)
        out << a.r;
    else if(a.i > 0)
        out << a.r << "+" <<a.i<<"i";
    else if(a.i < 0)
        out << a.r << a.i <<"i";
    return out;
}

istream& operator >> (std::istream& in, Rectangular_Matrix& a)
{
    for(int i=0 ; i<a.lin ; i++)
        delete [] a.M[i];
    delete [] a.M;
    in>>a.lin>>a.col;
    while(a.lin == a.col)
    {
        cout<<"Matrix must not be Square. Try again:\n";
        in>>a.lin>>a.col;
    }
    a.M = new Complex *[a.lin];
    for (int i = 0; i < a.lin; i++)
        a.M[i] = new Complex[a.col];
    for (int i = 0; i < a.lin; i++)
        for (int j = 0; j < a.col; j++)
            in >> a.M[i][j];
    return in;
}
ostream& operator << (std::ostream& out, Rectangular_Matrix& a)
{
    for(int i=0 ; i<a.lin ; i++)
    {
        for (int j = 0; j < a.col; j++)
            out << a.M[i][j] << " ";
        out<<"\n";
    }
    return out;
}

istream& operator >> (std::istream& in, Square_Matrix& a)
{
    for(int i=0 ; i<a.dim ; i++)
        delete [] a.M[i];
    delete [] a.M;
    in>>a.dim;
    a.M = new Complex *[a.dim];
    for (int i = 0; i < a.dim; i++)
        a.M[i] = new Complex[a.dim];
    for (int i = 0; i < a.dim; i++)
        for (int j = 0; j < a.dim; j++)
            in >> a.M[i][j];
    return in;
}
ostream& operator << (std::ostream& out, Square_Matrix& a)
{
    Complex d = a.det();
    out<<"det:"<<d<<"\n";
    for(int i=0 ; i<a.dim ; i++)
    {
        for (int j = 0; j < a.dim; j++)
            out << a.M[i][j] << " ";
        out<<"\n";
    }
    return out;
}

int main()
{
    Square_Matrix a(0) , b(0) , f(0);
    Rectangular_Matrix c(0,0) , d(0,0) , e(0,0);
    cin>>a;
    b = a.inverse();
    //c = a+b;
    //c = a * b;
    cout<<a<<"\n"<<b;
    cin>>c>>d;
    e = c + c;
    cout<<e;
    f = a*b;
    cout<<f;
    //Complex d = a.det();
    //delete a;
}