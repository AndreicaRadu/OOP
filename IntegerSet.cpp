#include <iostream>
#include <fstream>
using namespace std;
//ifstream fin("set.in"); ofstream fout("set.out");
class Node;
class LinkedList;
class IntegerSet;
class Pair;
class LinkedPairList;
class PairSet;

class Node
{
    Node* next;
    int data;

public:
    Node& operator =(Node const& A)
    {
        this->next = A.next;
        this->data = A.data;
        return *this;
    }

    friend class LinkedList;
    friend class IntegerSet;
    friend istream & operator >>(istream& in , IntegerSet& S);
    friend ostream & operator <<(ostream& out , IntegerSet& S);
    friend IntegerSet operator -(const IntegerSet& A , const IntegerSet& B);
    friend IntegerSet operator +(const IntegerSet& A , const IntegerSet& B);
    friend IntegerSet operator ^(const IntegerSet& A , const IntegerSet& B);
    friend PairSet operator *(const IntegerSet& A , const IntegerSet& B);

};

class LinkedList
{
    int length;
    Node* head;

public:
    LinkedList()
    {
        this->length = 0;
        this->head = nullptr;
    }

    ~LinkedList()
    {
        this->length = 0;
        Node* current = this->head;
        while( current )
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
        this->head = nullptr;
        cout << "//deleted list\n";
    }

    void add(int data)
    {
        Node* node = new Node();
        node->data = data;
        node->next = this->head;
        this->head = node;
        this->length++;
    }
    void print()
    {
        Node* head = this->head;
        int i = 1;
        while(head)
        {
            std::cout << i << ": " << head->data << std::endl;
            head = head->next;
            i++;
        }
    }

    LinkedList& operator =(LinkedList const& A)
    {
        delete this;

        this->length = A.length;
        Node* a = A.head;
        for(int i=0 ; i<A.length ; i++)
        {
            this->add(a->data);
            a = a->next;
        }
        return *this;
    }

    friend class IntegerSet;
    friend istream & operator >>(istream& in , IntegerSet& S);
    friend ostream & operator <<(ostream& out , IntegerSet& S);
    friend IntegerSet operator +(const IntegerSet& A , const IntegerSet& B);

};

class IntegerSet
{
    int cardinal;
    Node* head;

public:
    IntegerSet()
    {
        this->cardinal = 0;
        this->head = nullptr;
    }
    ~IntegerSet()
    {
        this->cardinal = 0;
        Node* current = this->head;
        while( current )
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
        this->head = nullptr;
        cout<<"//deleted integer set\n";
    }

    int part_of_set(IntegerSet* A , int x)
    {
        int ans = 0;
        Node* a = A->head;
        for(int i=0 ; i<A->cardinal ; i++)
        {
            if(a->data == x)
            {
                ans = 1;
                break;
            }
            a = a->next;
        }
        return ans;
    }

    void getset(LinkedList* S)
    {
        this->head = new Node();
        Node* h = S->head;
        Node* it = this->head;
        while(h)
        {
            if(!part_of_set(this , h->data))
            {
                this->cardinal++;
                it->data = h->data;
                it->next = new Node();
                it = it->next;
            }
            h = h->next;
        }
    }

    IntegerSet& operator =(IntegerSet const& A)
    {
        LinkedList L;
        L.length = A.cardinal;
        Node* head = A.head;
        for(int i=1 ; i<=A.cardinal ; i++)
        {
            L.add(head->data);
            head = head->next;
        }
        this->getset(&L);
        return *this;
    }

    friend ostream & operator <<(ostream& out , IntegerSet& S);
    friend IntegerSet operator -(const IntegerSet& A , const IntegerSet& B);
    friend IntegerSet operator +(const IntegerSet& A , const IntegerSet& B);
    friend IntegerSet operator ^(const IntegerSet& A , const IntegerSet& B);
    friend bool operator ==(const IntegerSet& A , const IntegerSet& B);
    friend PairSet operator *(const IntegerSet& A , const IntegerSet& B);

};

class Pair
{
    Pair* next;
    int x;
    int y;

public:
    Pair& operator =(Pair const& A)
    {
        this->next = A.next;
        this->x = A.x;
        this->y = A.y;
        return *this;
    }

    friend class LinkedPairList;
    friend class PairSet;
    friend istream & operator >>(istream& in , Pair& S);
    friend ostream & operator <<(ostream& out , Pair& S);
    friend istream & operator >>(istream& in , PairSet& S);
    friend ostream & operator <<(ostream& out , PairSet& S);
    friend PairSet operator *(const IntegerSet& A , const IntegerSet& B);
    friend PairSet operator +(const PairSet& A , const PairSet& B);

};

class LinkedPairList
{
    int length;
    Pair* head;

public:
    LinkedPairList()
    {
        this->length = 0;
        this->head = nullptr;
    }
    ~LinkedPairList()
    {
        this->length = 0;
        Pair* current = this->head;
        while( current )
        {
            Pair* next = current->next;
            delete current;
            current = next;
        }
        this->head = nullptr;
        cout<<"//deleted linked pair list\n";
    }

    void add(int x , int y)
    {
        Pair* pair = new Pair();
        pair->x = x;
        pair->y = y;
        pair->next = this->head;
        this->head = pair;
        this->length++;
    }

    LinkedPairList& operator =(LinkedPairList const& A)
    {
        delete this;

        this->length = A.length;
        Pair* a = A.head;
        for(int i=0 ; i<A.length ; i++)
        {
            this->add(a->x , a->y);
            a = a->next;
        }
        return *this;
    }

    friend class PairSet;
    friend istream & operator >>(istream& in , PairSet& S);
    friend ostream & operator <<(ostream& out , PairSet& S);
    friend PairSet operator +(const PairSet& A , const PairSet& B);

};

class PairSet
{
    int cardinal;
    Pair* head;

public:
    PairSet()
    {
        this->cardinal = 0;
        this->head = nullptr;
    };

    ~PairSet()
    {
        this->cardinal = 0;
        Pair* current = this->head;
        while( current )
        {
            Pair* next = current->next;
            delete current;
            current = next;
        }
        this->head = nullptr;
    }

    int part_of_set(PairSet* A , int x , int y)
    {
        int ans = 0;
        Pair* a = A->head;
        for(int i=0 ; i<A->cardinal ; i++)
        {
            if(a->x == x && a->y == y)
            {
                ans = 1;
                break;
            }
            a = a->next;
        }
        return ans;
    }

    void getpairset(LinkedPairList* S)
    {
        this->head = new Pair();
        Pair* h = S->head;
        Pair* it = this->head;
        while(h)
        {
            if(!part_of_set(this , h->x , h->y))
            {
                this->cardinal++;
                it->x = h->x;
                it->y = h->y;
                it->next = new Pair();
                it = it->next;
            }
            h = h->next;
        }
    }

    PairSet& operator =(PairSet const& A)
    {
        LinkedPairList L;
        L.length = A.cardinal;
        Pair* head = A.head;
        for(int i=1 ; i<=A.cardinal ; i++)
        {
            L.add(head->x , head->y);
            head = head->next;
        }
        this->getpairset(&L);
        return *this;
    }

    friend ostream & operator <<(ostream& out , PairSet& S);
    friend PairSet operator *(const IntegerSet& A , const IntegerSet& B);
    friend PairSet operator +(const PairSet& A , const PairSet& B);

};

istream & operator >>(istream& in , IntegerSet& S)
{
    LinkedList A;
    Node* c = new Node;
    A.head = c;
    in>>A.length;
    Node* a = A.head;
    for(int i=0 ; i<A.length ; i++)
    {
        in>>a->data;
        if(i<A.length-1)
        {
            a->next = new Node();
            a = a->next;
        }
    }
    S.getset(&A);
    return in;
}

ostream & operator <<(ostream& out , IntegerSet& S)
{
    Node* head = S.head;
    for(int i=1 ; i<=S.cardinal ; i++)
    {
        out << i << ": " << head->data << std::endl;
        head = head->next;
    }
    return out;
}

istream & operator >>(istream& in , Pair& S)
{
    in>>S.x;
    in>>S.y;
    S.next = new Pair();
    return in;
}

ostream & operator <<(ostream& out , Pair& S)
{
    out<<S.x<<" "<<S.y;
    return out;
}

istream & operator >>(istream& in , PairSet& S)
{
    LinkedPairList A;
    A.head = new Pair();
    in>>A.length;
    Pair* a = A.head;
    for(int i=0 ; i<A.length ; i++)
    {
        cin>>*a;
        if(i<A.length-1)
            a = a->next;
        else a->next = nullptr;
    }
    S.getpairset(&A);
    return in;
}

ostream & operator <<(ostream& out , PairSet& S)
{
    Pair* head = S.head;
    for(int i=1 ; i<=S.cardinal ; i++)
    {
        out << i << ": " << head->x << " "<< head->y << std::endl;
        head = head->next;
    }
    return out;
}

IntegerSet operator +(const IntegerSet& A , const IntegerSet& B)
{
    IntegerSet R;
    LinkedList Aux;
    Aux.head = new Node();
    Aux.length = A.cardinal + B.cardinal;
    Node* aux = Aux.head;
    Node* a = A.head;
    for(int i=0 ; i<A.cardinal ; i++)
    {
        aux->data = a->data;
        aux->next = new Node();
        aux = aux->next;
        a = a->next;
    }

    a = B.head;
    for(int i=0 ; i<B.cardinal ; i++)
    {
        aux->data = a->data;
        if(i<B.cardinal-1)
        {
            aux->next = new Node();
            aux = aux->next;
            a = a->next;
        }
    }
    R.getset(&Aux);
    return R;
}

IntegerSet operator ^(const IntegerSet& A , const IntegerSet& B)
{
    IntegerSet R;
    R.head = new Node();
    R.cardinal = 0;
    Node* x = R.head;
    Node* y = A.head;
    for(int i=0 ; i<A.cardinal ; i++)
    {
        int ans = 0;
        Node* a = B.head;
        for(int j=0 ; j<B.cardinal ; j++)
        {
            if(a->data == y->data)
            {
                ans = 1;
                j = B.cardinal+1;
            }
            a = a->next;
        }
        if(ans==1)
        {
            x->data = y->data;
            x->next = new Node();
            x = x->next;
            R.cardinal++;
        }
        y = y->next;
    }
    return R;
}

bool operator ==(const IntegerSet& A , const IntegerSet& B)
{
    if(A.cardinal != B.cardinal)
        return false;
    IntegerSet C = A + B;
    if(C.cardinal != A.cardinal)
        return false;
    return true;
}

bool operator !=(const IntegerSet& A , const IntegerSet& B)
{
    if(A==B) return false;
    else return true;
}

IntegerSet operator -(const IntegerSet& A , const IntegerSet& B)
{
    IntegerSet R;
    R.head = new Node();
    R.cardinal = 0;
    Node* x = R.head;
    Node* y = A.head;
    for(int i=0 ; i<A.cardinal ; i++)
    {
        int ans = 1;
        Node* a = B.head;
        for(int j=0 ; j<B.cardinal ; j++)
        {
            if(a->data == y->data)
            {
                ans = 0;
                j = B.cardinal+1;
            }
            a = a->next;
        }
        if(ans==1)
        {
            x->data = y->data;
            x->next = new Node();
            x = x->next;
            R.cardinal++;
        }
        y = y->next;
    }
    return R;
}

PairSet operator *(const IntegerSet& A , const IntegerSet& B)
{
    PairSet* R = new PairSet();
    R->cardinal = A.cardinal * B.cardinal;
    R->head = new Pair();
    Pair* r = R->head;
    Node* a = A.head;
    Node* b = B.head;
    for(int i=0 ; i<A.cardinal ; i++)
    {
        for(int j=0 ; j<B.cardinal ; j++)
        {
            r->x = a->data;
            r->y = b->data;
            b = b->next;
            r->next = new Pair();
            r = r->next;
        }
        a = a->next;
        b = B.head;
    }
    return *R;
}

PairSet operator +(const PairSet& A , const PairSet& B)
{
    PairSet R;
    LinkedPairList Aux;
    Aux.head = new Pair();
    Aux.length = A.cardinal + B.cardinal;
    Pair* aux = Aux.head;
    Pair* a = A.head;
    for(int i=0 ; i<A.cardinal ; i++)
    {
        aux->x = a->x;
        aux->y = a->y;
        aux->next = new Pair();
        aux = aux->next;
        a = a->next;
    }

    a = B.head;
    for(int i=0 ; i<B.cardinal ; i++)
    {
        aux->x = a->x;
        aux->y = a->y;
        if(i<B.cardinal-1)
        {
            aux->next = new Pair();
            aux = aux->next;
            a = a->next;
        }
    }
    R.getpairset(&Aux);
    return R;
}


int main()
{
    //transformare din lista in multime
    LinkedList A;
    IntegerSet M;
    int n0;
    cout<<"cate elemente?\n"; cin>>n0;
    for(int i=0 ; i<n0 ; i++)
    {
        int a; cin>>a;
        A.add(a);
    }
    M.getset(&A);
    cout<<M<<"\n";

    //citirea si memorarea a n obiecte
    int n;
    cout<<"cate multimi citim?\n";
    cin>>n;
    IntegerSet* A1 = new IntegerSet[n];
    for(int i=0 ; i<n ; i++)
        cin>>A1[i];
    for(int i=0 ; i<n ; i++)
        cout<<A1[i];

    //reuniune si intersectie
    IntegerSet Reun = A1[0]+A1[1];
    cout<<"Reuniunea primei cu a doua de mai devreme este\n"<<Reun<<"\n";
    IntegerSet Inter;
    Inter = A1[0] ^ A1[1];
    cout<<"Intersectia primei cu a doua de mai devreme este\n"<<Inter<<"\n";
    IntegerSet Dif = A1[0] - A1[1];
    cout<<"Diferenta primei cu a doua de mai devreme este\n"<<Dif<<"\n";

    //produs cartezian
    IntegerSet C1 , C2;
    PairSet C;
    cin>>C1>>C2;
    C = C1 * C2;
    cout<<C;
}