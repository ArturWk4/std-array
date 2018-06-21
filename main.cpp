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
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::const_reverse_iterator<iterator>;
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
    reference front();
    reference back();
    pointer data() noexcept;

    iterator begin() noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator crbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator crend() const noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;

    void fill(const T& value);
};

// Implicitly-defined member functions

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
    return storage[array_size-1];
}

template<class T, std::size_t N>
typename array<T, N>::pointer array<T, N>::data() noexcept
{
    return storage;
}

//-------------------------------------------------
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
    return storage + array_size;
}

template<class T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const noexcept
{
    return storage + array_size;
}

// Capacity

template<class T, std::size_t N>
bool array<T, N>::empty() const noexcept
{
    return array_size == 0;
}






}



int main()
{
    my::array<int, 4> a{2, 4, 1, 14};

    for(my::array<int, 4>::iterator i = a.begin(); i != a.end(); ++i)
    std::cout << *i << std::endl;
    return 0;
}
