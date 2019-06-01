//Andreica Radu-Adrian 135 CLion
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class statie;
class statieE;
class statieU;

struct Adresa
{
    string strada;
    int nr;
    int sector;
};
struct codstatie
{
    string tip;
    int numr;
};

class statie
{
    string nume;
    Adresa adresa;
public:
    statie() = default;
    ~statie() = default;

    string get_name()
    {
        return this->nume;
    }
    bool corect_address(string a , int b , int c)
    {
        return(a == this->adresa.strada && b == this->adresa.nr && c == this->adresa.sector);
    }
    friend istream& operator >> (istream& in , statieE& A);
    friend ostream& operator << (ostream& out , statieE& A);
    friend istream& operator >> (istream& in , statieU& A);
    friend ostream& operator << (ostream& out , statieU& A);
};

class statieE : public statie
{
    vector <int> bus;
    int nrbus;
    codstatie cod;
public:
    statieE()
    {
        this->cod.tip = "SE";
    }
    ~statieE()
    {
        this->bus.clear();
    }

    void set_code(int num)
    {
        this->cod.numr = num;
    }
    bool corect_code(string a , int b)
    {
        return(a == this->cod.tip && b == this->cod.numr);
    }
    bool find_bus(int a)
    {
        bool ans = false;
        for(int i=0 ; i<bus.size() ; i++)
            if(bus[i] == a)
                ans = true;
        return ans;
    }

    friend istream& operator >> (istream& in , statieE& A);
    friend ostream& operator << (ostream& out , statieE& A);
};

class statieU : public statie
{
    vector <int> bus;
    int nrbus;
    codstatie cod;
public:
    statieU()
    {
        this->cod.tip = "SU";
    }
    ~statieU()
    {
        this->bus.clear();
    }

    void set_code(int num)
    {
        this->cod.numr = num;
    }
    bool corect_code(string a , int b)
    {
        return(a == this->cod.tip && b == this->cod.numr);
    }
    bool find_bus(int a)
    {
        bool ans = false;
        for(int i=0 ; i<bus.size() ; i++)
            if(bus[i] == a)
                ans = true;
        return ans;
    }
    friend istream& operator >> (istream& in , statieU& A);
    friend ostream& operator << (ostream& out , statieU& A);
};

istream& operator >> (istream& in , statieE& A)
{
    cout<<"Nume statie: ";
    in>>A.nume;
    cout<<"Adresa este (strada, nr, sector): ";
    in>>A.adresa.strada>>A.adresa.nr>>A.adresa.sector;
    cout<<"Cate autobuze trec?";
    int a;
    in>>a;
    A.nrbus = a;
    for(int i=0 ; i<a ; i++)
    {
        int b;
        in>>b;
        A.bus.push_back(b);
    }
    return in;
}
ostream& operator << (ostream& out , statieE& A)
{
    out << A.nume << "\n" << A.adresa.strada << " numarul " << A.adresa.nr << " sector " << A.adresa.sector<< "\n";
    return out;
}
istream& operator >> (istream& in , statieU& A)
{
    cout<<"Nume statie: ";
    in>>A.nume;
    cout<<"Adresa este (strada, nr, sector): ";
    in>>A.adresa.strada>>A.adresa.nr>>A.adresa.sector;
    cout<<"Cate autobuze trec?";
    int a;
    in>>a;
    A.nrbus = a;
    for(int i=0 ; i<a ; i++)
    {
        int b;
        in>>b;
        A.bus.push_back(b);
    }
    return in;
}
ostream& operator << (ostream& out , statieU& A)
{
    out << A.nume << "\n" << A.adresa.strada << " numarul " << A.adresa.nr << " sector " << A.adresa.sector << "\n";
    return out;
}

int main()
{
    vector <statieE> VE(100);
    int counterVE = 0;
    vector <statieU> VU(100);
    int counterVU = 0;

    int op;
    cout<<"Cate operatii doriti sa faceti?"<<"\n";
    cin>>op;

    for(int i=0 ; i<op ; i++)
    {
        cout<<"Operatia "<<i<<" (introduceti 1 pt adaugare statie, 2 pt afisare statie 3 pt traseu autobuz 4 pt estimare pret" << "\n";
        int opi;
        cin>>opi;
        if(opi>4 || opi<1)
        {
            cout<<"Numar invalid"<<"\n";
            i--;
            continue;
        }
        if(opi == 1)
        {
            cout << "Introduceti 1 pt urbana 2 pt extraurbana" << "\n";
            int optip;
            cin >> optip;
            if(optip == 1)
            {
                cin >> VE[counterVE];
                VE[counterVE].set_code(counterVE + 100);
                counterVE++;
            }
            if(optip == 2)
            {
                cin >> VU[counterVU];
                VE[counterVU].set_code(counterVU + 100);
                counterVU++;
            }
        }
        if(opi == 2)
        {
            int optip;
            cout << "Introduceti 1 pt nume 2 pt adresa 3 pt cod" << "\n";
            cin >> optip;
            if(optip == 1)
            {
                string a;
                cin >> a;
                bool gasit = false;
                for(int j=0 ; j<counterVE ; j++)
                    if(a == VE[j].get_name())
                    {
                        cout << VE[j];
                        gasit = true;
                        break;
                    }
                if(!gasit)
                    for(int j=0 ; j<counterVU ; j++)
                        if(a == VU[j].get_name())
                        {
                            cout << VU[j];
                            gasit = true;
                            break;
                        }
                if(!gasit)
                    cout << "Nu exista aceasta statie" << "\n";
            }
            if(optip == 2)
            {
                string a;
                int b , c;
                cin >> a >> b >> c;
                bool gasit = false;
                for(int j=0 ; j<counterVE ; j++)
                    if(VE[j].corect_address(a , b , c))
                    {
                        cout << VE[j];
                        gasit = true;
                        break;
                    }
                if(!gasit)
                    for(int j=0 ; j<counterVU ; j++)
                        if(VU[j].corect_address(a , b , c))
                        {
                            cout << VU[j];
                            gasit = true;
                            break;
                        }
                if(!gasit)
                    cout << "Nu exista aceasta statie" << "\n";
            }
            if(optip == 3)
            {
                string a;
                int b;
                cout << "Introduceti SE pt extraurbana si SU pt urbana urmata de numarul de ordine al statiei" << "\n";
                cin >> a >> b;
                bool gasit = false;
                for(int j=0 ; j<counterVE ; j++)
                    if(VE[j].corect_code(a , b))
                    {
                        cout << VE[j];
                        gasit = true;
                        break;
                    }
                if(!gasit)
                    for(int j=0 ; j<counterVU ; j++)
                        if(VU[j].corect_code(a , b))
                        {
                            cout << VU[j];
                            gasit = true;
                            break;
                        }
                if(!gasit)
                    cout << "Nu exista aceasta statie" << "\n";
            }
        }
        if(opi == 3)
        {
            int nra;
            cout << "Nr autobuz va rog:" << "\n";
            cin >> nra;
            for(int j=0 ; j<counterVE ; j++)
                if(VE[j].find_bus(nra))
                    cout << VE[j].get_name() << "\n";             //am ales sa afisez doar numele pentru a nu afisa toate datele statiei (pt ca sunt multe) , se poate inlocui in cod cu VE[j]
            for(int j=0 ; j<counterVU ; j++)
                if(VU[j].find_bus(nra))
                    cout << VU[j].get_name() << "\n";
        }
        if(opi == 4)
        {
            cout << "Introduceti numele statiilor: " << "\n";
            string nume1 , nume2;
            cin >> nume1 >> nume2;
            bool lindir = false;
            //gasim daca e linie directa
            //trecem prin fiecare bus din nume1 (nu am apucat sa fac functia) si vedem cu find_bus daca exista si in nume2 (daca exista lindir primeste true)
            //apoi cu 4 if-uri vedem in ce caz se situeaza si afisam pretul
        }
    }

    return 0;
}













