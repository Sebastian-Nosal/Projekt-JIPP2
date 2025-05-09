/*#include "SmartArray.h"

template<typename T>
void SmartArray<T>::setSizeAndCapacity(unsigned size) {
    _size = 0;
    _capacity = ((size/100)+1)*100;
}

template<typename T>
void SmartArray<T>::reallocate(unsigned new_capacity) {
    T* temp = new T[new_capacity];
    unsigned current_size = (new_capacity < _size) ? new_capacity : _size;
    for (unsigned i = 0; i < current_size; ++i) {
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;
    _capacity = new_capacity;
}

template<typename T>
SmartArray<T>::SmartArray() {
    setSizeAndCapacity(0);
    data  = new T[_capacity];
}

template<typename T>
SmartArray<T>::SmartArray(unsigned size) {
    setSizeAndCapacity(size);
    data = new T[_capacity];
}

template<typename T>
SmartArray<T>::SmartArray(unsigned size, const T& elem) {
    setSizeAndCapacity(size);
    data = new T[_capacity];
    _size = size;
    for (unsigned i = 0; i < size; ++i)
        data[i] = elem;
}

template<typename T>
SmartArray<T>::~SmartArray() {
    delete[] data;
}

template<typename T>
T& SmartArray<T>::operator[](unsigned index){
    return data[index];
}

template<typename T>
bool SmartArray<T>::operator==(const SmartArray& array) const {
    if (_size != array._size)
        return false;
    for (unsigned i = 0; i < _size; ++i)
        if (data[i] != array.data[i])
            return false;
    return true;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const SmartArray<T>& array) {
    os << "[";
    for (unsigned i = 0; i < array._size; ++i) {
        os << array.data[i];
        if (i != array._size - 1) os << ", ";
    }
    os << "]";
    return os;
}

template<typename T>
T SmartArray<T>::at(unsigned index) {
    if (index >= _size) throw std::out_of_range("Index out of range");
    return data[index];
}

template<typename T>
const T SmartArray<T>::at(unsigned index) const {
    if (index >= _size) throw std::out_of_range("Index out of range");
    return data[index];
}

template<typename T>
bool SmartArray<T>::isEmpty() const {
    return _size == 0;
}

template<typename T>
unsigned SmartArray<T>::size() const {
    return _size;
}

template<typename T>
unsigned SmartArray<T>::capacity() const {
    return _capacity;
}

template<typename T>
void SmartArray<T>::reserve(unsigned size) {
    if (size > _capacity)
        reallocate(size);
}

template<typename T>
void SmartArray<T>::resize(unsigned size) {
    if (size > _capacity)
        reallocate(size);
    _size = size;
}

template<typename T>
void SmartArray<T>::resize(unsigned size, const T& elem) {
    if (size > _capacity)
        reallocate(size);
    for (unsigned i = _size; i < size; ++i)
        data[i] = elem;
    _size = size;
}

template<typename T>
void SmartArray<T>::clear() {
    delete[] data;
    data = new T[_capacity];
    _size = 0;
}

template<typename T>
void SmartArray<T>::insert(unsigned index, const T& elem) {
    if (index > _size) throw std::out_of_range("Index out of range");
    if (_size == _capacity)
        reallocate(_capacity+100);
    for (int i = _size - 1; i >= static_cast<int>(index); --i) {
        data[i + 1] = data[i];
    }
    data[index] = elem;
    ++_size;
}

template<typename T>
void SmartArray<T>::erase(unsigned index) {
    if (index >= _size) throw std::out_of_range("Index out of range");
    for (unsigned i = index; i < _size - 1; ++i)
        data[i] = data[i + 1];
    --_size;
}

template<typename T>
void SmartArray<T>::erase(unsigned index, unsigned amount) {
    if (amount > _size || index >= _size || index + amount > _size) throw std::out_of_range("Index + amount out of range");
    for (unsigned i = index; i + amount < _size; ++i)
        data[i] = data[i + amount];
    _size -= amount;
}

template<typename T>
void SmartArray<T>::pushBack(const T& elem) {
    if (_size == _capacity)
        reallocate(_capacity+100);
    data[_size++] = elem;
}

template<typename T>
void SmartArray<T>::popBack() {
    if (_size > 0) --_size;
}

template<typename T>
void SmartArray<T>::pushFront(const T& elem) {
    insert(0, elem);
}

template<typename T>
void SmartArray<T>::popFront() {
    erase(0);
}

template<typename T>
void SmartArray<T>::shrinkToFit() {
    reallocate(_size);
}
*/