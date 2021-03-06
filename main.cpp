#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <array>
#include <algorithm>
namespace my
{
template<class T, std::size_t N>
class array
{
    friend bool operator==(const my::array<T, N>& op1, const my::array<T, N>& op2);
    friend bool operator!=(const my::array<T, N>& op1, const my::array<T, N>& op2);
    friend bool operator<(const my::array<T, N>& op1,  const my::array<T, N>& op2);
    friend bool operator<=(const my::array<T, N>& op1, const my::array<T, N>& op2);
    friend bool operator>(const my::array<T, N>& op1,  const my::array<T, N>& op2);
    friend bool operator>=(const my::array<T, N>& op1, const my::array<T, N>& op2);
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
    using reverse_iterator = std::reverse_iterator<iterator>;
private:
    size_type reserved_size = N;
    size_type array_size = 0;
    T* storage;
public:
    array();
    array(std::initializer_list<T> _list);
    ~array();
    void operator=(array<T, N>& second);

    reference at(size_type pos);
    reference operator[](size_type pos);
    reference front();
    reference back();
    pointer data() noexcept;

    iterator begin() noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;

    void fill(const T& value);
    void swap(array<T, N>& other) noexcept;
};

// Implicitly-defined member functions

template<class T, std::size_t N>
array<T, N>::array()
{
    storage = new T[reserved_size];
    for(size_type i = 0; i < reserved_size; ++i)
        storage[i] = 0;
}

template<class T, std::size_t N>
array<T, N>::array(std::initializer_list<T> _list)
{
    storage = new T[reserved_size];
    for(size_type i = 0; i < reserved_size; ++i)
    {
        if(array_size < _list.size())
            storage[i] = *(_list.begin() + i);
        else
            storage[i] = 0;
        ++array_size;
    }
}

template<class T, std::size_t N>
array<T, N>::~array()
{
    delete [] storage;
}

template<class T, std::size_t N>
void array<T, N>::operator=(array<T, N>& second)
{
    for(iterator i = this->begin(), j = second.begin(); i != this->end(); ++i, ++j)
        *i = *j;
}


//------------------------------------------------------------------
// Element-access


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

template<class T, std::size_t N>
typename array<T, N>::reference array<T, N>::front()
{
    return storage[0];
}

template<class T, std::size_t N>
typename array<T, N>::reference array<T, N>::back()
{
    return storage[reserved_size-1];
}

template<class T, std::size_t N>
typename array<T, N>::pointer array<T, N>::data() noexcept
{
    return storage;
}

//------------------------------------------------------------------
//Iterators

template<class T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept
{
    return storage;
}

template<class T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin() const noexcept
{
    return storage;
}

template<class T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept
{
    return storage + reserved_size;
}

template<class T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const noexcept
{
    return storage + reserved_size;
}

//------------------------------------------------------------------
// Capacity

template<class T, std::size_t N>
bool array<T, N>::empty() const noexcept
{
    return array_size == 0;
}

template<class T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const noexcept
{
    return array_size;
}

template<class T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const noexcept
{
    return reserved_size;
}

//------------------------------------------------------------------
// Operations

template<class T, std::size_t N>
void array<T, N>::fill(const T& value)
{
    for(iterator i = this->begin(); i != this->end(); ++i)
        *i = value;
}

template<class T, std::size_t N>
void array<T, N>::swap(array<T, N>& other) noexcept
{
    for(typename array<T, N>::iterator i = this->begin(), j = other.begin(); i != this->end(); ++i, ++j)
        std::swap(*i, *j);
}

//------------------------------------------------------------------
// Non-member functions

template<class T, std::size_t N>
bool operator==( my::array<T, N>& op1, my::array<T, N>& op2)
{
    for(typename array<T, N>::iterator i = op1.begin(), j = op2.begin(); i != op1.end(); ++i, ++j)
        if(*i != *j)
            return false;
    return true;
}

template<class T, std::size_t N>
bool operator!=(my::array<T, N>& op1, my::array<T, N>& op2)
{
    return !(op1 == op2);
}

template<class T, std::size_t N>
bool operator<(my::array<T, N>& op1, my::array<T, N>& op2)
{
    for(typename array<T, N>::iterator i = op1.begin(), j = op2.begin(); i != op1.end(); ++i, ++j)
    {
        if(*i < *j)
            return true;
        if(*j < *i)
            return false;
    }
}

template<class T, std::size_t N>
bool operator>(my::array<T, N>& op1, my::array<T, N>& op2)
{
    for(typename array<T, N>::iterator i = op1.begin(), j = op2.begin(); i != op1.end(); ++i, ++j)
    {
        if(*i > *j)
            return true;
        if(*j > *i)
            return false;
    }
}

}




int main()
{
    my::array<int, 6> a{1,2,3,4,5,6};
    my::array<int, 6> b{1,3,3,4,5,6};


    for(my::array<int, 6>::iterator i = b.begin(); i != b.end(); ++i)
        std::cout << *i << "\n";

    return 0;
}
