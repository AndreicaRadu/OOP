#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Address
{
public:
    string country;
    string city;
    string street;
    int nr;
    Address(){}
    ~Address(){}

    bool operator == (Address const& a)
    {
        return(this->nr == a.nr && this->city == a.city && this->street == a.street && this->country == this->country);
    }
};
class Complex
{
public:
    int r;
    int i;

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

    Complex& operator = (Complex const& a) = default;
    bool operator == (Complex const& a)
    {
        return(this->r == a.r && this->i == a.i);
    }
    Complex operator + (const Complex& a)
    {
        Complex b;
        b.r = a.r + r;
        b.i = a.i + i;
        return b;
    }
    friend istream& operator >> (istream& in, Complex& a);
    friend ostream& operator << (ostream& out, Complex& a);
};

template <class A , class B , class C , class D = Address>
class Data
{
    int type;  //1=text 2=number 3=complex 4=adress
    A text;
    B number;
    C complex;
    D address;
public:
    string name;
    int ID;
    Data() = default;
    ~Data() = default;

    Data& operator = (Data const& a) = default;
    bool operator == (Data const& a)
    {
        return (this->complex == a.complex && this->number == a.number && this->text == a.text && this->address == a.address);
    }
    Data& operator + (Data const& a)
    {
        Data* b = new Data();
        b->name = this->name;
        b->ID = this->ID;
        b->type = this->type;
        b->number = this->number + a.number;
        b->complex = this->complex + a.complex;
        b->text = this->text + a.text;
        return *b;
    }

    friend istream& operator >> (istream& in , Data<string , int , Complex , Address>& a);
    friend ostream& operator << (ostream& out , Data<string , int , Complex , Address>& a);

    void setID(unsigned int a)
    {
        this->ID = a;
    }
    int get_type()
    {
        return this->type;
    }
    bool search_by_number(int a)
    {
        return this->number == a;
    }
    bool search_by_address(Address a)
    {
        return (this->address.country == a.country && this->address.city == a.city && this->address.street == a.street && this->address.nr == a.nr);
    }
    bool search_by_text(string a)
    {
        return this->text == a;
    }
    bool search_by_complex(Complex a)
    {
        return (this->complex.r == a.r && this->complex.i == a.i);
    }
};

istream& operator >> (istream& in, Complex& a)
{
    in >> a.r;
    in >> a.i;
    return in;
}
ostream& operator << (ostream& out, Complex& a)
{
    if(a.i == 0)
        out << a.r << "\n";
    else if(a.i > 0)
        out << a.r << "+" <<a.i<<"i" << "\n";
    else if(a.i < 0)
        out << a.r << a.i <<"i" << "\n";
    return out;
}
istream& operator >> (istream& in , Data<string , int , Complex , Address>& a)
{
    cout << "1 pentru text 2 pentru numar 3 pentru complex 4 pentru adresa ENTER apoi datele\n";
    in >> a.type;
    if (a.type == 1)
        in >> a.text;
    else if (a.type == 2)
        in >> a.number;
    else if (a.type == 3)
        in >> a.complex;
    else if (a.type == 4)
        in >> a.address.country >> a.address.city >> a.address.street >> a.address.nr;
    cout << "Doriti ca datele sa primeasca un nume? (0 pt NU , 1 pt DA)\n";
    int x;
    in >> x;
    if(x == 1)
        in >> a.name;
    return in;
}
ostream& operator << (ostream& out , Data<string , int , Complex , Address>& a)
{
    if (a.type == 1)
        out << a.text << "\n";
    else if (a.type == 2)
        out << a.number << "\n";
    else if (a.type == 3)
        out << a.complex << "\n";
    else if (a.type == 4)
        out << a.address.country << "\n" << a.address.city << "\n" << a.address.street << "\n" << a.address.nr << "\n";
    return out;
}

int main()
{
    cout << "Cate operatii doriti sa efectuati?\n";
    int nr;
    cin >> nr;
    vector <Data<string , int , Complex>> V;
    unsigned int count = 0;
    Data<string , int , Complex> del;
    queue<unsigned int> q;
    for(int i=1 ; i<=nr ; i++)
    {
        cout << "Operatia numarul " << i << " (1 pt adaugare; 2 pt stergere; 3 cautare dupa nume/ID; 4 cautare dupa informatie):\n";
        int k;
        cin >> k;
        if(k == 1)
        {
            Data<string , int , Complex> D;
            cin >> D;
            bool a = false;
            if(!D.name.empty())
            {
                for(int j=0 ; j<count ; j++)
                    if(V[j].name == D.name)
                    {
                        if(V[j].get_type() != D.get_type() || V[j].get_type() == 4)
                            cout << "Exista informatii retinute cu acest nume. Datele nu au fost memorate.\n";
                        else
                            V[j] = V[j] + D;
                        a = true;
                    }
            }

            if(q.empty() && !a)
            {
                count++;
                V.resize(count);
                V[count - 1] = D;
                cout << "ID-ul informatiei este " << count - 1 << "\n";
                V[count - 1].setID(count - 1);
            } else if(!a){
                unsigned int aux = q.front();
                q.pop();
                V[aux] = D;
                cout << "ID-ul informatiei este " << aux << "\n";
                V[aux].setID(aux);
            }
        }
        if(k == 2)
        {
            cout << "1 pt stergere dupa ID; 2 pt stergere dupa nume" << "\n";
            int aux;
            cin >> aux;
            if(aux == 1)
            {
                unsigned int aid;
                cin >> aid;
                q.push(aid);
                if(aid < count)
                    V[aid] = del;
            }
            if(aux == 2)
            {
                string num;
                cin >> num;
                for(unsigned int j=0 ; j<count ; j++)
                    if(V[j].name == num)
                    {
                        V[j] = del;
                        q.push(j);
                        j = count;
                    }
            }
        }
        if(k == 3)
        {
            cout << "1 pt cautare dupa ID; 2 pt cautare dupa nume" << "\n";
            int aux;
            cin >> aux;
            if(aux == 1)
            {
                int auxi;
                cin >> auxi;
                if(auxi < count)
                    cout << V[auxi] << "\n";
                else
                    cout << "Nu exista informatii cu acest ID";
            }
            if(aux == 2)
            {
                string num;
                cin >> num;
                for(int j=0 ; j<count ; j++)
                    if(V[j].name == num)
                    {
                        cout << V[j] << "\n";
                        j = count;
                    }
            }
        }
        if(k == 4)
        {
            cout << "1 pentru text 2 pentru numar 3 pentru complex 4 pentru adresa ENTER apoi datele\n";
            int aux;
            cin >> aux;
            if(aux == 1)
            {
                string num;
                cin >> num;
                for(int j=0 ; j<count ; j++)
                    if(V[j].search_by_text(num))
                        cout << "Informatia este stocata cu ID " << j << "\n";
            }
            if(aux == 2)
            {
                int num;
                cin >> num;
                for(int j=0 ; j<count ; j++)
                    if(V[j].search_by_number(num))
                        cout << "Informatia este stocata cu ID " << j << "\n";
            }
            if(aux == 3)
            {
                Complex num;
                cin >> num;
                for(int j=0 ; j<count ; j++)
                    if(V[j].search_by_complex(num))
                        cout << "Informatia este stocata cu ID " << j << "\n";
            }
            if(aux == 4)
            {
                Address num;
                cin >> num.country >> num.city >> num.street >> num.nr;
                for(int j=0 ; j<count ; j++)
                    if(V[j].search_by_address(num))
                        cout << "Informatia este stocata cu ID " << j << "\n";
            }
        }
    }
    V.clear();
    return 0;
}