#pragma once
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "handler.h"
#include <iostream>


/**
 * @class TUI
 * @brief Tekstowy interfejs użytkownika do interakcji z danymi studentów.
 *
 * Klasa TUI (Text-based User Interface) odpowiada za prezentację danych oraz obsługę
 * formularzy w postaci TUI.
 * Komunikuje się z klasą `Handler`, która zarządza logiką aplikacji.
 */
 class TUI {
    private:
        /**
         * @brief Wartość wprowadzona przez użytkownika, używana do wyświeltania pofiltrowanych danych.
         */
        std::string inputValue;
    
        /**
         * @brief Referencja do obiektu klasy Handler obsługującego logikę aplikacji.
         */
        Handler& handler;
    
        /**
         * @brief Wyświetla formularz dodawania nowego studenta.
         * @param screen Obiekt ekranu ftxui.
         */
        void showAddForm(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Wyświetla formularz usuwania studenta.
         * @param screen Obiekt ekranu ftxui.
         */
        void showRemoveForm(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Wyświetla listę wszystkich studentów.
         * @param screen Obiekt ekranu ftxui.
         */
        void showList(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Wyświetla formularz aktualizacji danych studenta.
         * @param screen Obiekt ekranu ftxui.
         */
        void showUpdateForm(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Wyświetla średnią ocen pogrupowaną według semestrów.
         * @param screen Obiekt ekranu ftxui.
         */
        void showAvgBySemester(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Wyświetla najlepszego studenta/studentów (na podstawie średniej).
         * @param screen Obiekt ekranu ftxui.
         */
        void showBestStudent(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Filtruje i pokazuje studentów według imienia.
         * @param screen Obiekt ekranu ftxui.
         */
        void showByFirstname(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Filtruje i pokazuje studentów według nazwiska.
         * @param screen Obiekt ekranu ftxui.
         */
        void showByLastname(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Pokazuje studentów ze średnią >= względem wprowadzonemu kryterium.
         * @param screen Obiekt ekranu ftxui.
         */
        void showAboveAverage(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Pokazuje studentów ze średnią <= względem wprowadzonemu kryterium.
         * @param screen Obiekt ekranu ftxui.
         */
        void showBelowAverage(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Pokazuje studentów na semestrze <= wprowadzonemu kryterium.
         * @param screen Obiekt ekranu ftxui.
         */
        void showAboveSemester(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Pokazuje studentów na semestrze >= wprowadzonemu kryterium.
         * @param screen Obiekt ekranu ftxui.
         */
        void showBelowSemester(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Pokazuje studenta znajdującego się na określonej pozycji (N-ty) na liście.
         * @param screen Obiekt ekranu ftxui.
         */
        void showNth(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Pokazuje studentów z zakresu od N do K.
         * @param screen Obiekt ekranu ftxui.
         */
        void showNtoK(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Filtruje i wyszukuje studentów imieniu i nazwisku (2 kryteria).
         * @param screen Obiekt ekranu ftxui.
         */
        void showByFullName(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Oblicza i pokazuje średnią ocen dla podanego semestru.
         * @param screen Obiekt ekranu ftxui.
         */
        void showAvgByGivenSemester(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Pokazuje ogólną średnią wszystkich studentów.
         * @param screen Obiekt ekranu ftxui.
         */
        void showOverallAverage(ftxui::ScreenInteractive& screen);
    
        /**
         * @brief Pokazuje liczbę studentów w bazie.
         * @param screen Obiekt ekranu ftxui.
         */
        void showSize(ftxui::ScreenInteractive& screen);
    
    public:
        /**
         * @brief Konstruktor klasy TUI.
         * @param handlerRef Referencja do obiektu klasy Handler, która zarządza danymi.
         */
        TUI(Handler& handlerRef);
    };
    