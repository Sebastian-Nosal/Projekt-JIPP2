#pragma once
#include "data.h"
#include "SmartArray.h"
#include <iostream>
#include <functional>

/**
 * @class Handler
 * @brief Klasa odpowiedzialna za zarządzanie listą studentów oraz za wykonywanie operacji na danych.
 *
 * Klasa udostępnia metody do dodawania, usuwania, aktualizacji oraz filtrowania studentów.
 * Obsługuje również operacje zapisu/odczytu danych z plików (tekstowych i binarnych).
 */
 class Handler {
    private:
        /**
         * @brief Dynamiczna tablica studentów typu SmartArray.
         */
        SmartArray<Student> data;
    
    public:
        /**
         * @brief Konstruktor domyślny klasy Handler.
         */
        Handler();
    
        /**
         * @brief Dodaje nowego studenta na podstawie danych wejściowych.
         * 
         * @param firstname Imię studenta.
         * @param lastname Nazwisko studenta.
         * @param average Średnia ocen (jako string do sparsowania).
         * @param semester Semestr (jako string do sparsowania).
         * @return true jeśli dodano pomyślnie, false w przeciwnym razie.
         */
        bool add(std::string firstname,
                 std::string lastname,
                 std::string average,
                 std::string semester);
    
        /**
         * @brief Usuwa studenta na podstawie ID.
         * 
         * @param id Identyfikator studenta (jako string do sparsowania).
         * @return true jeśli usunięto, false jeśli nie znaleziono.
         */
        bool remove(std::string id);
    
        /**
         * @brief Zwraca wskaźnik na tablicę studentów.
         * 
         * @return Wskaźnik na pierwszy element tablicy.
         */
        Student* list();
    
        /**
         * @brief Zwraca liczbę studentów w kolekcji.
         * 
         * @return Ilość studentów jako int.
         */
        int getSize();
    
        /**
         * @brief Aktualizuje dane istniejącego studenta na podstawie ID lub tworzy nowego.
         * 
         * @param searchId Identyfikator studenta (jako string do sparsowania).
         * @param firstname Nowe imię.
         * @param lastname Nowe nazwisko.
         * @param average Nowa średnia ocen (jako string do sparsowania).
         * @param semester Nowy semestr (jako string do sparsowania).
         * @return true jeśli zaktualizowano, false jeśli wystąpił błąd parsowania.
         */
        bool update(std::string searchId,
                    std::string firstname,
                    std::string lastname,
                    std::string average,
                    std::string semester);
    
        /**
         * @brief Zwraca studentów spełniających określone kryterium.
         * 
         * @param predicate Funkcja filtrująca przyjmująca obiekt Student, zazwyczaj jako wyrażenie lambda.
         * @param outSize Zmienna wyjściowa przechowująca rozmiar zwróconej listy.
         * @return Wskaźnik na tablicę spełniających warunki studentów.
         */
        Student* listByCriteria(std::function<bool(const Student&)> predicate, int& outSize);
    
        /**
         * @brief Wczytuje dane studentów z pliku binarnego.
         * 
         * @return true jeśli wczytano, false w przeciwnym razie.
         */
        bool loadFromBinary();
    
        /**
         * @brief Zapisuje dane studentów do pliku binarnego.
         * 
         * @return true jeśli zapisano, false w przeciwnym razie.
         */
        bool saveToBinary();
    
        /**
         * @brief Wczytuje dane studentów z pliku tekstowego.
         * 
         * @return true jeśli wczytano, false w przeciwnym razie.
         */
        bool loadFromFile();
    
        /**
         * @brief Zapisuje dane studentów do pliku tekstowego.
         * 
         * @return true jeśli zapisano, false w przeciwnym razie.
         */
        bool saveToFile();
    
        /**
         * @brief Oblicza średnią ocen studentów dla podanego semestru.
         * 
         * @param semester Numer semestru.
         * @return Średnia ocen.
         */
        double getAverageOfSemester(int semester);
    
        /**
         * @brief Zwraca najlepszych studentów (np. o najwyższej średniej).
         * 
         * @param amount referencja do zmiennej określająca ilość zwróconych studentów.
         * @return Wskaźnik na tablicę najlepszych studentów.
         */
        Student* getBestStudents(int& amount);
    
        /**
         * @brief Zwraca studenta o określonym indeksie.
         * 
         * @param idx Indeks studenta.
         * @return Obiekt Student znajdujący się na danym indeksie.
         */
        Student getByIdx(int idx);
    
        /**
         * @brief Zwraca tablicę studentów w zakresie od N do K (lub odwrotnie).
         * 
         * @param n Początkowy indeks.
         * @param k Końcowy indeks.
         * @param output_length Zmienna wyjściowa określająca długość zwróconej tablicy.
         * @return Wskaźnik na tablicę studentów w zakresie.
         */
        Student* getFromNtoK(int n, int k, int& output_length);
    
        /**
         * @brief Oblicza ogólną średnią ocen wszystkich studentów.
         * 
         * @return Średnia ocen.
         */
        double getOverallAverage();
    };
    