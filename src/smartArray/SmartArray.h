#ifndef SMARTARRAY_H
#define SMARTARRAY_H

#include <iostream>
#include <stdexcept>

/**
 * @brief Szablon dynamicznej tablicy z funkcjonalnością podobną do std::vector.
 * 
 * Klasa SmartArray zapewnia dynamiczną alokację pamięci, automatyczne zarządzanie rozmiarem 
 * i funkcje do manipulacji danymi w stylu kontenerów STL.
 * 
 * @tparam T Typ przechowywanych elementów.
 */
template <typename T>
class SmartArray {
private:
    T* data;               ///< Wskaźnik na dynamicznie alokowaną tablicę.
    unsigned _size;        ///< Aktualna liczba elementów w tablicy.
    unsigned _capacity;    ///< Całkowita dostępna pojemność.

    /// @brief Zmienia pojemność tablicy do podanej wartości.
    /// @param new_capacity Nowa pojemność.
    void reallocate(unsigned new_capacity) {
        T* temp = new T[new_capacity];
        unsigned current_size = (new_capacity < _size) ? new_capacity : _size;
        for (unsigned i = 0; i < current_size; ++i) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        _capacity = new_capacity;
    }

    /// @brief Ustawia  rozmiar na 0 i pojemność tablicy na najmniejszą wielokrotność 100 większą od podanej wartości.
    /// @param size Nowa pojemność
    void setSizeAndCapacity(unsigned size) {
        _size = 0;
        _capacity = ((size/100)+1)*100;
    }

public:
    /// @brief Konstruktor domyślny.
    SmartArray() {
        setSizeAndCapacity(0);
        data  = new T[_capacity];
    }

    /// @brief Konstruktor tworzący tablicę o zadanym rozmiarze.
    /// @param size Liczba elementów.
    SmartArray(unsigned size) {
        setSizeAndCapacity(size);
        data = new T[_capacity];
    }

    /// @brief Konstruktor tworzący tablicę wypełnioną danym elementem.
    /// @param size Liczba elementów.
    /// @param elem Wartość do przypisania.
    SmartArray(unsigned size, const T& elem) {
        setSizeAndCapacity(size);
        data = new T[_capacity];
        _size = size;
        for (unsigned i = 0; i < size; ++i)
            data[i] = elem;
    }

    /// @brief Konstruktor kopiujący.
    /// @param left Smart array który ma być skopiowany.
    SmartArray(const SmartArray& left) {
        _size = left.size();
        _capacity = left.capacity();
        data = new T[_capacity];
        for (unsigned i=0;i<_size;i++) {
            data[i] = left.data[i];
        }
    }

    /// @brief Destruktor, zwalnia zaalokowaną pamięć.
    ~SmartArray() {
        delete[] data;
    }

    /// @brief Dostęp do elementu bez kontroli zakresu.
    /// @param index Indeks elementu.
    /// @return Referencja do elementu.
    T& operator[](unsigned index) {
        return data[index];
    }

    /// @brief Operator porównania dwóch tablic.
    /// @param array Inna tablica.
    /// @return true jeśli tablice są identyczne.
    bool operator==(const SmartArray& array) const {
        if (_size != array._size)
            return false;
        for (unsigned i = 0; i < _size; ++i)
            if (data[i] != array.data[i])
                return false;
        return true;
    }

    /// @brief Operator przypisania kopiującego.
    ///
    /// Kopiuje zawartość jednej instancji SmartArray do drugiej. Jeśli przypisywana
    /// jest ta sama instancja (samo-przypisanie), nic się nie dzieje.
    ///
    /// @param other Źródłowa instancja SmartArray, z której mają zostać skopiowane dane.
    /// @return Referencja do bieżącego obiektu po przypisaniu.
    SmartArray& operator=(const SmartArray& other) {
        if (this == &other) return *this; // samo-przypisanie
    
        delete[] data; // zwolnij starą pamięć
    
        _size = other._size;
        _capacity = other._capacity;
        data = new T[_capacity];
        for (unsigned i = 0; i < _size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    /// @brief Zwraca element na danym indeksie z kontrolą zakresu.
    /// @param index Indeks elementu.
    /// @return Kopia elementu.
    /// @throw std::out_of_range jeśli indeks jest nieprawidłowy.
    T& at (unsigned index){
        if (index >= _size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    /// @brief Wersja const metody at().
    const T at(unsigned index) const{
        if (index >= _size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    /// @brief Sprawdza, czy tablica jest pusta.
    /// @return true jeśli tablica nie zawiera elementów.
    bool isEmpty() const {
        return _size == 0;
    }

    /// @brief Zwraca aktualny rozmiar tablicy.
    unsigned size() const {
        return _size;
    }

    /// @brief Zwraca aktualną pojemność tablicy.
    unsigned capacity() const {
        return _capacity;
    }

    /// @brief Rezerwuje miejsce na określoną liczbę elementów.
    /// @param size Liczba elementów do zarezerwowania.
    void reserve(unsigned size) {
        if (size > _capacity)
            reallocate(size);
    }

    /// @brief Zmienia rozmiar tablicy.
    /// @param size Nowy rozmiar.
    void resize(unsigned size){
        if (size > _capacity)
            reallocate(size);
        _size = size;
    }

    /// @brief Zmienia rozmiar i ustawia nowe elementy na daną wartość.
    /// @param size Nowy rozmiar.
    /// @param elem Wartość nowych elementów.
    void resize(unsigned size, const T& elem) {
        if (size > _capacity)
            reallocate(size);
        for (unsigned i = _size; i < size; ++i)
            data[i] = elem;
        _size = size;
    }

    /// @brief Usuwa wszystkie elementy.
    void clear() {
        delete[] data;
        data = new T[_capacity];
        _size = 0;
    }

    /// @brief Zmniejsza pojemność do aktualnego rozmiaru.
    void shrinkToFit() {
        reallocate(_size);
    }

    /// @brief Wstawia element na określonym indeksie.
    /// @param index Indeks wstawienia.
    /// @param elem Wstawiany element.
    void insert(unsigned index, const T& elem) {
        if (index > _size) throw std::out_of_range("Index out of range");
        if (_size == _capacity)
            reallocate(_capacity+100);
        for (int i = _size - 1; i >= static_cast<int>(index); --i) {
            data[i + 1] = data[i];
        }
        data[index] = elem;
        ++_size;
    }

    /// @brief Usuwa jeden element na wskazanym indeksie.
    /// @param index Indeks do usunięcia.
    void erase(unsigned index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        for (unsigned i = index; i < _size - 1; ++i)
            data[i] = data[i + 1];
        --_size;
    }

    /// @brief Usuwa kilka elementów od danego indeksu.
    /// @param index Indeks początkowy.
    /// @param amount Liczba elementów do usunięcia.
    void erase(unsigned index, unsigned amount) {
        if (amount > _size || index >= _size || index + amount > _size) throw std::out_of_range("Index + amount out of range");
        for (unsigned i = index; i + amount < _size; ++i)
            data[i] = data[i + amount];
        _size -= amount;
    }

    /// @brief Dodaje element na końcu.
    /// @param elem Element do dodania.
    void pushBack(const T& elem) {
        if (_size == _capacity)
            reallocate(_capacity+100);
        data[_size++] = elem;
    }

    /// @brief Usuwa ostatni element.
    void popBack() {
        if (_size > 0) --_size;
    }

    /// @brief Dodaje element na początku.
    /// @param elem Element do dodania.
    void pushFront(const T& elem) {
        insert(0, elem);
    }

    /// @brief Usuwa pierwszy element.
    void popFront() {
        erase(0);
    }
    
    /**
     * @brief Operator wyjścia strumieniowego do wypisywania zawartości.
     * 
     * @tparam U Typ elementów.
     * @param os Strumień wyjściowy.
     * @param array Tablica do wypisania.
     * @return Strumień po wypisaniu.
     */
    template <typename U>
    friend std::ostream& operator<<(std::ostream&, const SmartArray<U>&);
};

template <typename U>
std::ostream& operator<<(std::ostream& os, const SmartArray<U>& array) {
    os << "[";
    for (unsigned i = 0; i < array._size; ++i) {
        os << array.data[i];
        if (i != array._size - 1) os << ", ";
    }
    os << "]";
    return os;
}

#endif
