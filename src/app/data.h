#pragma once
#include <iostream>
#include <string>

/**
 * @class Student
 * @brief Reprezentuje pojedynczego studenta z podstawowymi danymi.
 *
 * Klasa przechowuje informacje o imieniu, nazwisku, średniej ocen, semestrze oraz identyfikatorze studenta..
 */
 class Student {
    private:
        /**
         * @brief Unikalny identyfikator studenta.
         */
        int id;
    
        /**
         * @brief Imię studenta.
         */
        std::string firstname;
    
        /**
         * @brief Nazwisko studenta.
         */
        std::string lastname;
    
        /**
         * @brief Średnia ocen studenta.
         */
        double average;
    
        /**
         * @brief Semestr, na którym aktualnie znajduje się student.
         */
        int semester;
    
        /**
         * @brief Statyczne pole przechowujące kolejny dostępny identyfikator.
         */
        static int next_id;
    
    public:
        /**
         * @brief Domyślny konstruktor studenta.
         *
         * Tworzy nowego studenta z domyślnymi wartościami i automatycznie przypisanym identyfikatorem.
         */
        Student();
    
        /**
         * @brief Konstruktor tworzący studenta bez podanego identyfikatora.
         *
         * @param fname Imię studenta.
         * @param lname Nazwisko studenta.
         * @param avg Średnia ocen.
         * @param sem Semestr.
         */
        Student(std::string fname, std::string lname, double avg, int sem);
    
        /**
         * @brief Konstruktor tworzący studenta z podanym identyfikatorem.
         *
         * @param id Identyfikator studenta.
         * @param fname Imię studenta.
         * @param lname Nazwisko studenta.
         * @param avg Średnia ocen.
         * @param sem Semestr.
         */
        Student(int id, std::string fname, std::string lname, double avg, int sem);
    
        /**
         * @brief Pobiera imię studenta.
         * @return Imię jako std::string.
         */
        std::string getFirstName() const;
    
        /**
         * @brief Pobiera nazwisko studenta.
         * @return Nazwisko jako std::string.
         */
        std::string getLastName() const;
    
        /**
         * @brief Pobiera aktualny semestr studenta.
         * @return Numer semestru jako int.
         */
        int getSemester() const;
    
        /**
         * @brief Pobiera średnią ocen studenta.
         * @return Średnia ocen jako double.
         */
        double getAverage() const;
    
        /**
         * @brief Pobiera identyfikator studenta.
         * @return Identyfikator jako int.
         */
        int getId() const;
    
        /**
         * @brief Przeciażenie operatora strumienia wyjścia do wypisywania danych studenta.
         * @param os Strumień wyjściowy.
         * @param s Obiekt studenta.
         * @return Referencja do strumienia wyjściowego.
         */
        friend std::ostream& operator<<(std::ostream& os, const Student& s);
    };