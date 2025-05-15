#pragma once
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "handler.h"
#include <iostream>


class TUI {
    private:
        std::string inputValue;
        Handler& handler;
        void showAddForm(ftxui::ScreenInteractive& screen);
        void showRemoveForm(ftxui::ScreenInteractive& screen);
        void showList(ftxui::ScreenInteractive& screen);
        void showUpdateForm(ftxui::ScreenInteractive& screen);
        void showAvgBySemester(ftxui::ScreenInteractive& screen);
        void showBestStudent(ftxui::ScreenInteractive& screen);
        void showByFirstname(ftxui::ScreenInteractive& screen);
        void showByLastname(ftxui::ScreenInteractive& screen);
        void showAboveAverage(ftxui::ScreenInteractive& screen);
        void showBelowAverage(ftxui::ScreenInteractive& screen);
        void showAboveSemester(ftxui::ScreenInteractive& screen);
        void showBelowSemester(ftxui::ScreenInteractive& screen);
        void showNth(ftxui::ScreenInteractive& screen);
        void showNtoK(ftxui::ScreenInteractive& screen);
        void showByFullName(ftxui::ScreenInteractive& screen);
        void showAvgByGivenSemester(ftxui::ScreenInteractive& screen);
        void showOverallAverage(ftxui::ScreenInteractive& screen);

    public:
        TUI(Handler& handlerRef);
    
};
