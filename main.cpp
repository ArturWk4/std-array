#include <iostream>
#include <initializer_list>
#include <stdexcept>

namespace my
{
template<class T, std::size_t N>
class array
{
    friend operator==(my::array<T, N>& op1, my::array<T, N>& op2);
    friend operator!=(my::array<T, N>& op1, my::array<T, N>& op2);
    friend operator<(my::array<T, N>& op1, my::array<T, N>& op2);
    friend operator<=(my::array<T, N>& op1, my::array<T, N>& op2);
    friend operator>(my::array<T, N>& op1, my::array<T, N>& op2);
    friend operator>=(my::array<T, N>& op1, my::array<T, N>& op2);
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = T*;
    using const_iterator = const T*;
private:
    size_type array_size = N;
    T* storage;
public:
    array();
    array(std::initializer_list<T> _list);
    ~array();
    array operator=(const array<T, N>& second);

    reference at(size_type pos);
    reference operator[](size_type pos);

};

// Implicitly-defined member functions
//-----------------------------------------------
template<class T, std::size_t N>
array<T, N>::array()
{
    storage = new T[array_size];
}

template<class T, std::size_t N>
array<T, N>::array(std::initializer_list<T> _list)
{
    if(_list.size() != array_size)
        throw std::out_of_range("Size of my::array and size of std::initialize_list should be equals!");
    storage = new T[array_size];
    for(size_type i = 0; i < array_size; ++i)
    {
        storage[i] = *(_list.begin() + i);
    }
}

template<class T, std::size_t N>
array<T, N>::~array()
{
    delete [] storage;
}

template<class T, std::size_t N>
array<T, N> array<T, N>::operator=(const array<T, N>& second)
{
    if(array_size != second.array_size)
        throw std::out_of_range("(operator=): Size of both my::arrays should be equals");

    for(size_type i = 0; i < array_size; ++i)
        storage[i] = second.storage[i];
    return *this;
}


//---------------------------------------------
// Element-access
//---------------------------------------------

template<class T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(array<T, N>::size_type pos)
{
    if(pos >= array_size)
        throw std::out_of_range("'Pos' can't be >= size of my::array!");
    return storage[pos];
}
template<class T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](array<T, N>::size_type pos)
{
    return storage[pos];
}

}


int main()
{
    my::array<int, 4> a{2, 4, 1, 14};
    my::array<int, 4> b = a;
    std::cout << a[3] << std::endl;
    return 0;
}
