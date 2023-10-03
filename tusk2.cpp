#include <iostream>
#include <vector>

using namespace std;

class Toy {
public:
    Toy(string _name) : name(_name) {};
    Toy() : Toy("Pidoras") {};
    virtual ~Toy() {};
private:
    string name;
};

class shared_ptr_toy {
private:
    Toy* hisToy;
    int* refCount;

public:
    shared_ptr_toy(string _name) {
        hisToy = new Toy(_name);
        refCount = new int(1);
    }
    shared_ptr_toy() : shared_ptr_toy("Ball") {};
    shared_ptr_toy(const shared_ptr_toy& other)
    {
        hisToy = other.hisToy;
        refCount = other.refCount;
        (*refCount)++; 
    }
    shared_ptr_toy& operator=(const shared_ptr_toy& other)
    {
        if (this == &other) return *this;

        if (refCount != nullptr)
        {
            (*refCount)--; 
            if (*refCount == 0)
            {
                delete hisToy; 
                delete refCount;
            }
        }

        hisToy = other.hisToy;
        refCount = other.refCount;
        (*refCount)++; 
        return *this;
    }
    ~shared_ptr_toy()
    {
        (*refCount)--;
        if (*refCount == 0)
        {
            delete hisToy; 
            delete refCount;
        }
    }
};

shared_ptr_toy make_shared_toy(string name)
{
    shared_ptr_toy obj(name);
    return obj;
}

shared_ptr_toy make_shared_toy(shared_ptr_toy other)
{
    shared_ptr_toy obj(other);
    return obj;
}

class Dog {
public:
    Dog(string _name, shared_ptr_toy Toy, int _age) : name(_name), lovelyToy(Toy) {
        if (age >= 0 && age < 30)
        {
            age = _age;
        }
        else
        {
            age = 0;
        }
    }
    Dog() : Dog("Snow", make_shared_toy("SomeToy"), 0) {};
    Dog(string _name) : Dog(_name, make_shared_toy("SomeToy"), 0) {};
    Dog(int _age) : Dog("Snow", make_shared_toy("SomeToy"), _age) {};

    void CopyToy(const Dog& other) {
        lovelyToy = other.lovelyToy;
    }

private:
    string name;
    int age;
    shared_ptr_toy lovelyToy;
};

int main() {
    shared_ptr_toy ball = make_shared_toy("Ball");
    shared_ptr_toy anotherBall = make_shared_toy(ball);

    Dog a("Vasya", ball, 10);
    Dog b("Stepa", ball, 11);
    Dog c("Artem", ball, 12);
}

/*
using namespace std;

class Toy {
public:
    Toy(string _name) : name(_name) {};
    Toy() : Toy("Pidoras") {};
private:
    string name;
};

class smart_ptr_toy {
private:
    Toy* obj;
public:
    smart_ptr_toy(string _name) {
        obj = new Toy(_name);
    }
    smart_ptr_toy() : smart_ptr_toy("somename") {};
    smart_ptr_toy(const smart_ptr_toy& other)
    {
        obj = new Toy(*other.obj);
    }
    smart_ptr_toy& operator = (const smart_ptr_toy& other)
    {
        if (this == &other) return *this;
        if (obj != nullptr) delete obj;
        obj = new Toy(*other.obj);
        return *this;
    }
    ~smart_ptr_toy()
    {
        delete obj;
    }
};

class Dog {
public:
    Dog(string _name, shared_ptr<Toy> Toy, int _age) : name(_name), lovelyToy(Toy) {
        if (age >= 0 && age < 30)
        {
            age = _age;
        }
        else
        {
            age = 0;
        }
    }
    Dog() : Dog("Snow", make_shared<Toy>("SomeToy"), 0) {};
    Dog(string _name) : Dog(_name, make_shared<Toy>("SomeToy"), 0) {};
    Dog(int _age) : Dog("Snow", make_shared<Toy>("SomeToy"), _age) {};

    void CopyToy(const Dog& other) {
        lovelyToy = other.lovelyToy;
    }

    void SetBestie(shared_ptr<Dog> _bestie)
    {
        Bestie = _bestie;
    }

private:
    string name;
    int age;
    shared_ptr<Toy> lovelyToy;
    weak_ptr<Dog> Bestie;
};

int main() {
    shared_ptr<Toy> ball = make_shared<Toy>("Ball");
    shared_ptr<Toy> dildo = make_shared<Toy>("Dildo");
    shared_ptr<Toy> govno = ball;

    shared_ptr<Dog> a = make_shared<Dog>("a", ball, 23);
    shared_ptr<Dog> b = make_shared<Dog>("b", ball, 13);
    shared_ptr<Dog> c = make_shared<Dog>("c", dildo, 10);

    a->SetBestie(b);
    b->SetBestie(a);

    ball.reset();
    dildo.reset();
}*/
