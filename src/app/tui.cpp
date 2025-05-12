#include "tui.h"
#include <string>
#include <vector>
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

void TUI::showAddForm(ScreenInteractive& screen) {
    std::string firstname, lastname, semester, avg;
    std::string info;

    auto form = Container::Vertical({
        Input(&firstname, "First Name"),
        Input(&lastname, "Last Name"),
        Input(&semester, "Semester"),
        Input(&avg, "Average of marks"),
        Button("Confirm Add", [&] {
            if (firstname.empty() || lastname.empty() || semester.empty() || avg.empty()) {
                info = "Fields cannot be empty.";
            } else {
                info = "Student added successfully!";
                firstname.clear();
                lastname.clear();
                semester.clear();
                avg.clear();
            }
        }),
        Button("Back", screen.ExitLoopClosure())
    });

    auto renderer = Renderer(form, [&] {
        return vbox({
            text("Add Student") | bold | center,
            separator(),
            form->Render(),
            separator(),
            text(info) | color(Color::Yellow) | center
        }) | border;
    });

    screen.Loop(renderer);
}

void TUI::showRemoveForm(ScreenInteractive& screen) {
    std::string id;
    std::string info;

    auto form = Container::Vertical({
        Input(&id, "Student ID"),
        Button("Confirm Remove", [&] {
            if (id.empty()) {
                info = "ID cannot be empty.";
            } else {
                info = "Student removed.";
                id.clear();
            }
        }),
        Button("Back", screen.ExitLoopClosure())
    });

    auto renderer = Renderer(form, [&] {
        return vbox({
            text("Remove Student") | bold | center,
            separator(),
            form->Render(),
            separator(),
            text(info) | color(Color::Yellow) | center
        }) | border;
    });

    screen.Loop(renderer);
}

void TUI::showList(ScreenInteractive& screen) {
    auto back_button = Button("Back", screen.ExitLoopClosure());

    auto container = Container::Vertical({
        back_button
    });

    auto renderer = Renderer(container, [&] {
        return vbox({
            text("List All Students") | bold | center,
            text("Showing student list...") | center,
            separator(),
            back_button->Render()
        }) | border;
    });

    screen.Loop(renderer);
}

void TUI::showUpdateForm(ScreenInteractive& screen) {
    screen.Loop(Renderer(Container::Vertical({
        Button("Back", screen.ExitLoopClosure())
    }), [] {
        return vbox({
            text("Update Student") | bold | center,
            text("Feature not implemented.") | color(Color::Red) | center
        }) | border;
    }));
}

void TUI::showAvgBySemester(ScreenInteractive& screen) {
    screen.Loop(Renderer(Container::Vertical({
        Button("Back", screen.ExitLoopClosure())
    }), [] {
        return vbox({
            text("Average GPA by Semester") | bold | center,
            text("Feature coming soon...") | center
        }) | border;
    }));
}

void TUI::showBestStudent(ScreenInteractive& screen) {
    screen.Loop(Renderer(Container::Vertical({
        Button("Back", screen.ExitLoopClosure())
    }), [] {
        return vbox({
            text("Best Student(s)") | bold | center,
            text("Feature coming soon...") | center
        }) | border;
    }));
}

void TUI::showSorted(ScreenInteractive& screen) {
    screen.Loop(Renderer(Container::Vertical({
        Button("Back", screen.ExitLoopClosure())
    }), [] {
        return vbox({
            text("Sort by Semester") | bold | center,
            text("Feature coming soon...") | center
        }) | border;
    }));
}

TUI::TUI(Handler& handlerRef): handler(handlerRef)  {
    this->handler = handlerRef;
    auto screen = ScreenInteractive::TerminalOutput();

    int selected = 0;
    std::string info_message;

    std::vector<std::string> options = {
        "Add Student",
        "Remove Student",
        "List All Students",
        "Update Student",
        "Get Average by semester",
        "Get Best Student(s)",
        "Sort By Semester",
        "Save To File",
        "Load From File",
        "Save To Binary File",
        "Load From Binary File",
        "Exit"
    };

    auto menu = Menu(&options, &selected);
    auto container = Container::Vertical({menu});

    auto renderer = Renderer(container, [&] {
        return vbox({
            text("Student Management System") | bold | center,
            separator(),
            menu->Render() | frame | center,
            separator(),
            text(info_message) | center | color(Color::Yellow)
        }) | border;
    });

    screen.Loop(CatchEvent(renderer, [&](Event e) {
        if (e == Event::Return) {
            switch (selected) {
                case 0: showAddForm(screen); break;
                case 1: showRemoveForm(screen); break;
                case 2: showList(screen); break;
                case 3: showUpdateForm(screen); break;
                case 4: showAvgBySemester(screen); break;
                case 5: showBestStudent(screen); break;
                case 6: showSorted(screen); break;
                case 7: info_message = "Data saved to file."; break;
                case 8: info_message = "Data loaded from file."; break;
                case 9: info_message = "Data saved to binary file."; break;
                case 10: info_message = "Data loaded from binary file."; break;
                case 11: screen.Exit(); break;
            }
            return true;
        }
        return false;
    }));
}
