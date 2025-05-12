#pragma once
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "handler.h"


class TUI {
    private:
        Handler& handler;
        //void showMenu(ftxui::ScreenInteractive& screen);
        void showAddForm(ftxui::ScreenInteractive& screen);
        void showRemoveForm(ftxui::ScreenInteractive& screen);
        void showList(ftxui::ScreenInteractive& screen);
        void showUpdateForm(ftxui::ScreenInteractive& screen);
        void showAvgBySemester(ftxui::ScreenInteractive& screen);
        void showBestStudent(ftxui::ScreenInteractive& screen);
        void showSorted(ftxui::ScreenInteractive& screen);
    public:
        TUI(Handler& handlerRef);
    
};
