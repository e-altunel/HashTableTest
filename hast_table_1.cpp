/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Object {
public:
    virtual void print(ostream & o) = 0;
    virtual Object * returncopy() = 0;
};

class IntObject : public Object {
    int value;
public:
    void print(ostream &o) {
        o << value;
    }
    const IntObject &operator=(int a) {
        value = a;
        return *this;
    }
    IntObject(int a) {
        value = a;
    }
    Object *returncopy() {
        return new IntObject(value);
    }
};

class DoubleObject : public Object {
    double value;
public:
    void print(ostream &o) {
        o << value;
    }
    const DoubleObject &operator=(double a) {
        value = a;
        return *this;
    }
    DoubleObject(double a) {
        value = a;
    }
    Object * returncopy() {
        return new DoubleObject(value);
    }
};

class StringObject : public Object {
    string value;
public:
    void print(ostream &o) {
        o << value;
    }
    const StringObject &operator=(const char *a) {
        value = a;
        return *this;
    }
    StringObject (const char *a) {
        value = a;
    }
    StringObject (string &a) {
        value = a;
    }
    Object * returncopy() {
        return new StringObject(value);
    }
};

ostream& operator<<(ostream& o, Object& obj) {
    obj.print(o);
    return o;
}

class HashTable {
    const int size = 30;
    Object ** ptr = nullptr;
    string * keys = nullptr;
public:
    int HashFunction(const string &s1) {
        int sum = 0;
        for (char x : s1)
            sum += x;
        return sum % size;
    }
    HashTable(int s) : size(s) {
        ptr = new Object* [s];
        keys = new string [s];
        for (int i = 0; i < s; i++)
            ptr[i] = nullptr;
    }
    void addElement(const string &key, Object * obj) {
        int loc = HashFunction(key);
        int locog = loc;
        while (ptr[loc] != nullptr) {
            ++loc;
            if (loc >= size)
                loc = 0;
            if (loc == locog)
                return;
        }
        keys[loc] = key;
        ptr[loc] = obj->returncopy();
    }
    Object *& operator[](const string &key) {
        int loc = HashFunction(key);
        int locog = loc;
        while (key != keys[loc])
        {
            loc++;
            if (loc == size)
                loc = 0;
            if (loc == locog)
                break;
        }
        return ptr[loc];
    }
};

int main() {
    
    HashTable table(30);
    
    IntObject a = 5;
    IntObject d = 10;
    
    table["Test"] = &a;
    table.addElement("Test<", &d);
    
    DoubleObject b = 5.1;
    
    table["Huseyin"] = &b;
    
    StringObject c = "Deneme";
    
    table["Emirhan"] = &c;

    cout << *table["Test"] << endl;
    cout << *table["Huseyin"] << endl;
    cout << *table["Emirhan"] << endl;
    cout << *table["Test<"] << endl;
    
    return 0;
}
