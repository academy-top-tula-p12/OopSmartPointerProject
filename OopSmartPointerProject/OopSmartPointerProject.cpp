#include <iostream>

template <typename T>
class SmartPointer
{
    T* pointer;
public:
    static int count;

    SmartPointer(T* pointer = nullptr)
        : pointer{ pointer } {}
    SmartPointer(const SmartPointer& sp)
    {
        pointer = sp.pointer;
        sp.pointer = nullptr;
    }

    ~SmartPointer() 
    {
        delete pointer;
    }
    T& operator*() const { return *pointer; }
    T* operator->() const { return pointer; }

    SmartPointer& operator=(const SmartPointer& sp)
    {
        if (&sp == this)
            return *this;

        delete pointer;
        pointer = sp.pointer;
        sp.pointer = nullptr;
        return *this;
    }
};



class Resource
{
    int value;
public:
    Resource()
    {
        value = 0;
        std::cout << "Resource construct\n";
    }
    Resource(const Resource& r)
    {
        value = r.value;
        std::cout << "Resource copy construct\n";
    }
    ~Resource()
    {
        std::cout << "Resource destruct\n";
    }

    int& Value() { return value; }
};

void Function()
{
    //Resource* res = new Resource();
    SmartPointer<Resource> sptr1(new Resource());
    sptr1->Value() = 100;
    SmartPointer<Resource> sptr2(new Resource());
    sptr2->Value() = 200;
    SmartPointer<Resource> sptr3(sptr2);

    std::cout << sptr1.count << " " << sptr1->Value() << "\n";
    std::cout << sptr2.count << " " << sptr2->Value() << "\n";
    std::cout << sptr3.count << " " << sptr3->Value() << "\n";
    
    SmartPointer<Resource> sptr4(sptr3);
    std::cout << sptr2.count << " " << sptr2->Value() << "\n";
    std::cout << sptr3.count << " " << sptr3->Value() << "\n";
    std::cout << sptr4.count << " " << sptr4->Value() << "\n";
    /*
    int x;
    std::cout << "input x: ";
    std::cin >> x;

    if (x == 0)
        //throw 0;
        return;

    sp->Value() = 100;
    */
    //delete res;
}

int main()
{
    Function();
}
