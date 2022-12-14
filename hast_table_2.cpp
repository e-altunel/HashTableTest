#include <iostream>
#include <string>

using namespace std;

class Object {
public:
    virtual void print(ostream & o) = 0;
    virtual Object * returncopy() = 0;
};
/*
class Int : public Object {
    int value;
public:
    void print(ostream &o) {
        o << value;
    }
    const Int &operator=(int a) {
        value = a;
        return *this;
    }
    Int(int a) {
        value = a;
    }
    Object *returncopy() {
        return new Int(value);
    }
};

class Double : public Object {
    double value;
public:
    void print(ostream &o) {
        o << value;
    }
    const Double &operator=(double a) {
        value = a;
        return *this;
    }
    Double(double a) {
        value = a;
    }
    Object * returncopy() {
        return new Double(value);
    }
};

class String : public Object {
    string value;
public:
    void print(ostream &o) {
        o << value;
    }
    const String &operator=(const char *a) {
        value = a;
        return *this;
    }
    String (const char *a) {
        value = a;
    }
    String (string &a) {
        value = a;
    }
    Object * returncopy() {
        return new String(value);
    }
};
*/

template <typename T>
class SubObject : public Object {
    T value;
public:
    void print(ostream &o) {
        o << value;
    }
    const SubObject &operator=(T a) {
        value = a;
        return *this;
    }
    SubObject(T a) {
        value = a;
    }
    Object *returncopy() {
        return new SubObject<T>(value);
    }
};

class ObjectElement {
private:
    Object * ptr = nullptr;
public:
    ObjectElement() {}
    ObjectElement(Object & obj) {
        ptr = obj.returncopy();
    }
    ObjectElement(const ObjectElement &obj) {
        if (this == &obj)
            return;
        if (ptr != nullptr)
            delete ptr;
        ptr = obj.ptr->returncopy();
    }
    ~ObjectElement() {
        delete ptr;
    }
    const ObjectElement & operator=(Object & obj) {
        ptr = obj.returncopy(); 
        return *this;
    }
    bool isEmpyt() const {
        if (ptr == nullptr)
        return true;
        return false;
    }
    friend ostream& operator<<(ostream& o, ObjectElement& obj);
};

ostream& operator<<(ostream& o, ObjectElement& obj) {
    obj.ptr->print(o);
    return o;
}

class HashTable {
    const int size = 30;
    ObjectElement * ptr = nullptr;
    string * keys = nullptr;
public:
    int HashFunction(const string &s1) {
        int sum = 0;
        for (char x : s1)
            sum += x;
        return sum % size;
    }
    HashTable(int s) : size(s) {
        ptr = new ObjectElement [s];
        keys = new string [s];
    }
    void addElement(const string &key, Object &obj) {
        int loc = HashFunction(key);
        int locog = loc;
        while (!ptr[loc].isEmpyt()) {
            ++loc;
            if (loc >= size)
                loc = 0;
            if (loc == locog)
                return;
        }
        keys[loc] = key;
        ptr[loc] = obj;
    }
    ObjectElement & operator[](const string &key) {
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
    ~HashTable() {
        delete[] ptr;
    }
};

int main() {
    
    HashTable table(30);
    
    SubObject<int> a = 5;
    SubObject<int> d = 10;
    
    table["Test"] = a;
    table.addElement("Test<", d);
    
    SubObject<double> b = 5.1;
    
    table["Huseyin"] = b;
    
    SubObject<const char *> c = "Deneme";
    
    table["Emirhan"] = c;
    table["Test<"] = d;

    cout << table["Test"] << endl;
    cout << table["Huseyin"] << endl;
    cout << table["Emirhan"] << endl;
    cout << table["Test<"] << endl;
    
    return 0;
}
