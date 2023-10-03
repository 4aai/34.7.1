#include <iostream>
#include <string>
#include <concepts>

template <typename T> concept ComplexConcept = requires(T v)
{
    {v.hash()}->std::convertible_to<long>;
    {v.toString()}->std::same_as<std::string>;
}&& !std::has_virtual_destructor<T>::value;

class Hash
{
public:
    Hash(int num) : _num(num) {}
    ~Hash() {}
    auto hash() { return _num; }
    auto toString() { return std::to_string(_num); }
private:
    int _num;
};


class HashVirtual 
{
public:
    HashVirtual(int num) : _num(num) {}
    virtual ~HashVirtual() {}
    auto hash() { return _num; }
    auto toString() { return std::to_string(_num); }
private:
    int _num;
};

class HashNoHash
{
public:
    HashNoHash(int num) : _num(num) {}
    ~HashNoHash() {}
    //auto hash() { return _num; }
    auto toString() { return std::to_string(_num); }
private:
    int _num;
};

template <ComplexConcept T>
void Concept(T v)
{
    std::cout << "\n" << typeid(v).name() << ":\n";
    std::cout << "\thash() return: " << v.hash() << "\n";
    std::cout << "\ttoString() return: " << v.toString() << "\n";
    std::cout << "\tvirtual destructor: " \
        << (std::has_virtual_destructor<T>::value ? "true" : "false") << "\n";
}

int main() 
{
    Hash h(123);
    Concept<Hash>(h);

    HashVirtual hv(456);
    //Concept<HashVirtual>(hv); // virtual ~destructor

    HashNoHash hnh(789);
    //Concept<HashNoHash>(hnh); // no hash method
    
    return 0;
}
