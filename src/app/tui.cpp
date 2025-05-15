#include "tui.h"
#include <string>
#include <vector>
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "data.h"
#include <functional>

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
                bool flag = this->handler.add(firstname,lastname,avg,semester);
                if(flag) info = "Student added successfully!";
                else info = "Improper field(s)";
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
                bool flag = this->handler.remove(id);
                if(flag) info = "Student removed.";
                else info = "Nothing to delete";
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
    Student* tmp = this->handler.list();
    int studentCount = this->handler.getSize();
    std::vector<Component> list_elems;

    for (int i = 0; i < studentCount; i++) {
        std::string element_content = 
            "ID: " + std::to_string(tmp[i].getId()) + " " +
            tmp[i].getFirstName() + " " + tmp[i].getLastName() +
            " Semester: " + std::to_string(tmp[i].getSemester()) +
            " Avg: " + std::to_string(tmp[i].getAverage());

        list_elems.push_back(ftxui::Renderer([element_content] {
            return ftxui::text(element_content);
        }));
    }

    auto back_button = ftxui::Button("Back", screen.ExitLoopClosure());
    list_elems.push_back(back_button);  // <- to jest kluczowe!

    auto container = ftxui::Container::Vertical(list_elems);

    auto renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
            ftxui::text("List of Students") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            container->Render()
        }) | ftxui::border;
    });
    delete[] tmp;
    screen.Loop(renderer);
}

void TUI::showUpdateForm(ScreenInteractive& screen) {
    std::string firstname, lastname, semester, avg,id;
    std::string info;

    auto form = Container::Vertical({
        Input(&id, "ID"),
        Input(&firstname, "First Name"),
        Input(&lastname, "Last Name"),
        Input(&semester, "Semester"),
        Input(&avg, "Average of marks"),
        Button("Confirm Add", [&] {
            if (id.empty() || firstname.empty() || lastname.empty() || semester.empty() || avg.empty()) {
                info = "Fields cannot be empty.";
            } else {
                bool flag = this->handler.update(id,firstname,lastname,avg,semester);
                if(flag) info = "Data updated";
                else info = "Improper field(s)";
                id.clear();
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

void TUI::showAvgBySemester(ScreenInteractive& screen) {

    std::vector<Component> list_elems;

    for (int i = 1; i <=8; i++) {
        std::string element_content = "Semester "+ std::to_string(i)+ " : "+std::to_string(this->handler.getAverageOfSemester(i));

        list_elems.push_back(ftxui::Renderer([element_content] {
            return ftxui::text(element_content);
        }));
    }

    auto back_button = ftxui::Button("Back", screen.ExitLoopClosure());
    list_elems.push_back(back_button);  // <- to jest kluczowe!

    auto container = ftxui::Container::Vertical(list_elems);

    auto renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
            ftxui::text("Average of each semester") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            container->Render()
        }) | ftxui::border;
    });

    screen.Loop(renderer);
}

void TUI::showBestStudent(ScreenInteractive& screen) {
    int amount;
    Student* tmp = this->handler.getBestStudents(amount);
    std::vector<Component> list_elems;

    for (int i = 0; i < amount; i++) {
        std::string element_content = 
            "ID: " + std::to_string(tmp[i].getId()) + " " +
            tmp[i].getFirstName() + " " + tmp[i].getLastName() +
            " Semester: " + std::to_string(tmp[i].getSemester()) +
            " Avg: " + std::to_string(tmp[i].getAverage());

        list_elems.push_back(ftxui::Renderer([element_content] {
            return ftxui::text(element_content);
        }));
    }

    auto back_button = ftxui::Button("Back", screen.ExitLoopClosure());
    list_elems.push_back(back_button);

    auto container = ftxui::Container::Vertical(list_elems);

    auto renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
            ftxui::text("List of Students") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            container->Render()
        }) | ftxui::border;
    });

    screen.Loop(renderer);
}

void TUI::showByFirstname(ftxui::ScreenInteractive& screen) {
    std::string input;

    std::vector<ftxui::Component> list_elems;

    auto form = ftxui::Container::Vertical({
        ftxui::Input(&input, "Enter first name"),
        ftxui::Button("Search", [&] {
            inputValue = input;
            input.clear();
            screen.PostEvent(ftxui::Event::Custom);  
        }),
        ftxui::Button("Back", screen.ExitLoopClosure())
    });

    auto renderer = ftxui::Renderer(form, [&] {
        std::vector<ftxui::Element> elements;

        elements.push_back(ftxui::text("Search by Firstname") | ftxui::bold | ftxui::center);
        elements.push_back(ftxui::separator());
        elements.push_back(form->Render());

        if (!inputValue.empty()) {
            int count = 0;
            Student* result = handler.listByCriteria(
                [&](const Student& s) {
                    return s.getFirstName() == inputValue;
                },
                count
            );

            list_elems.clear();

            elements.push_back(ftxui::separator());

            if (count == 0 || result == nullptr) {
                elements.push_back(ftxui::text("No matching students found."));
            } else {
                for (int i = 0; i < count; ++i) {
                    const Student& s = result[i];
                    std::string line = "ID: " + std::to_string(s.getId()) + " " +
                                       s.getFirstName() + " " + s.getLastName() +
                                       " Semester: " + std::to_string(s.getSemester()) +
                                       " Avg: " + std::to_string(s.getAverage());
                    elements.push_back(ftxui::text(line));
                }
                delete[] result;
            }

            inputValue.clear();
        }

        return ftxui::vbox(std::move(elements)) | ftxui::border;
    });

    screen.Loop(renderer);
}

void TUI::showByLastname(ftxui::ScreenInteractive& screen) {
    std::string input;

    std::vector<ftxui::Component> list_elems;

    auto form = ftxui::Container::Vertical({
        ftxui::Input(&input, "Enter last name"),
        ftxui::Button("Search", [&] {
            inputValue = input;
            input.clear();
            screen.PostEvent(ftxui::Event::Custom);
        }),
        ftxui::Button("Back", screen.ExitLoopClosure())
    });

    auto renderer = ftxui::Renderer(form, [&] {
        std::vector<ftxui::Element> elements;

        elements.push_back(ftxui::text("Search by Lastname") | ftxui::bold | ftxui::center);
        elements.push_back(ftxui::separator());
        elements.push_back(form->Render());

        if (!inputValue.empty()) {
            int count = 0;
            Student* result = handler.listByCriteria(
                [&](const Student& s) {
                    return s.getLastName() == inputValue;
                },
                count
            );

            list_elems.clear();

            elements.push_back(ftxui::separator());

            if (count == 0 || result == nullptr) {
                elements.push_back(ftxui::text("No matching students found."));
            } else {
                for (int i = 0; i < count; ++i) {
                    const Student& s = result[i];
                    std::string line = "ID: " + std::to_string(s.getId()) + " " +
                                       s.getFirstName() + " " + s.getLastName() +
                                       " Semester: " + std::to_string(s.getSemester()) +
                                       " Avg: " + std::to_string(s.getAverage());
                    elements.push_back(ftxui::text(line));
                }
                delete[] result;
            }

            inputValue.clear();
        }

        return ftxui::vbox(std::move(elements)) | ftxui::border;
    });

    screen.Loop(renderer);
}

void TUI::showAboveAverage(ftxui::ScreenInteractive& screen) {
    std::string input;

    std::vector<ftxui::Component> list_elems;

    auto form = ftxui::Container::Vertical({
        ftxui::Input(&input, "Enter minimal average"),
        ftxui::Button("Search", [&] {
            inputValue = input;
            input.clear();
            screen.PostEvent(ftxui::Event::Custom);  
        }),
        ftxui::Button("Back", screen.ExitLoopClosure())
    });

    auto renderer = ftxui::Renderer(form, [&] {
        std::vector<ftxui::Element> elements;

        elements.push_back(ftxui::text("Search by average") | ftxui::bold | ftxui::center);
        elements.push_back(ftxui::separator());
        elements.push_back(form->Render());

        if (!inputValue.empty()) {
            int count = 0;
            Student* result = handler.listByCriteria(
                [&](const Student& s) {
                    try {
                        return s.getAverage() >= std::stod(inputValue);
                    }
                    catch(const std::invalid_argument&) {
                        return false;
                    }

                },
                count
            );

            list_elems.clear();

            elements.push_back(ftxui::separator());

            if (count == 0 || result == nullptr) {
                elements.push_back(ftxui::text("No matching students found."));
            } else {
                for (int i = 0; i < count; ++i) {
                    const Student& s = result[i];
                    std::string line = "ID: " + std::to_string(s.getId()) + " " +
                                       s.getFirstName() + " " + s.getLastName() +
                                       " Semester: " + std::to_string(s.getSemester()) +
                                       " Avg: " + std::to_string(s.getAverage());
                    elements.push_back(ftxui::text(line));
                }
                delete[] result;
            }

            inputValue.clear();
        }

        return ftxui::vbox(std::move(elements)) | ftxui::border;
    });

    screen.Loop(renderer);
}

void TUI::showBelowAverage(ftxui::ScreenInteractive& screen) {
    std::string input;

    std::vector<ftxui::Component> list_elems;

    auto form = ftxui::Container::Vertical({
        ftxui::Input(&input, "Enter maximal average"),
        ftxui::Button("Search", [&] {
            inputValue = input;
            input.clear();
            screen.PostEvent(ftxui::Event::Custom);  
        }),
        ftxui::Button("Back", screen.ExitLoopClosure())
    });

    auto renderer = ftxui::Renderer(form, [&] {
        std::vector<ftxui::Element> elements;

        elements.push_back(ftxui::text("Search by average") | ftxui::bold | ftxui::center);
        elements.push_back(ftxui::separator());
        elements.push_back(form->Render());

        if (!inputValue.empty()) {
            int count = 0;
            Student* result = handler.listByCriteria(
                [&](const Student& s) {
                    try {
                        return s.getAverage() <= std::stod(inputValue);
                    }
                    catch(const std::invalid_argument&) {
                        return false;
                    }

                },
                count
            );

            list_elems.clear();

            elements.push_back(ftxui::separator());

            if (count == 0 || result == nullptr) {
                elements.push_back(ftxui::text("No matching students found."));
            } else {
                for (int i = 0; i < count; ++i) {
                    const Student& s = result[i];
                    std::string line = "ID: " + std::to_string(s.getId()) + " " +
                                       s.getFirstName() + " " + s.getLastName() +
                                       " Semester: " + std::to_string(s.getSemester()) +
                                       " Avg: " + std::to_string(s.getAverage());
                    elements.push_back(ftxui::text(line));
                }
                delete[] result;
            }

            inputValue.clear();
        }

        return ftxui::vbox(std::move(elements)) | ftxui::border;
    });

    screen.Loop(renderer);
}

void TUI::showAboveSemester(ftxui::ScreenInteractive& screen) {
    std::string input;

    std::vector<ftxui::Component> list_elems;

    auto form = ftxui::Container::Vertical({
        ftxui::Input(&input, "Enter minimal semester"),
        ftxui::Button("Search", [&] {
            inputValue = input;
            input.clear();
            screen.PostEvent(ftxui::Event::Custom);  
        }),
        ftxui::Button("Back", screen.ExitLoopClosure())
    });

    auto renderer = ftxui::Renderer(form, [&] {
        std::vector<ftxui::Element> elements;

        elements.push_back(ftxui::text("Search by semester") | ftxui::bold | ftxui::center);
        elements.push_back(ftxui::separator());
        elements.push_back(form->Render());

        if (!inputValue.empty()) {
            int count = 0;
            Student* result = handler.listByCriteria(
                [&](const Student& s) {
                    try {
                        return s.getSemester() >= std::stoi(inputValue);
                    }
                    catch(const std::invalid_argument&) {
                        return false;
                    }

                },
                count
            );

            list_elems.clear();

            elements.push_back(ftxui::separator());

            if (count == 0 || result == nullptr) {
                elements.push_back(ftxui::text("No matching students found."));
            } else {
                for (int i = 0; i < count; ++i) {
                    const Student& s = result[i];
                    std::string line = "ID: " + std::to_string(s.getId()) + " " +
                                       s.getFirstName() + " " + s.getLastName() +
                                       " Semester: " + std::to_string(s.getSemester()) +
                                       " Avg: " + std::to_string(s.getAverage());
                    elements.push_back(ftxui::text(line));
                }
                delete[] result;
            }

            inputValue.clear();
        }

        return ftxui::vbox(std::move(elements)) | ftxui::border;
    });

    screen.Loop(renderer);
}

void TUI::showBelowSemester(ftxui::ScreenInteractive& screen) {
    std::string input;

    std::vector<ftxui::Component> list_elems;

    auto form = ftxui::Container::Vertical({
        ftxui::Input(&input, "Enter maximal semester"),
        ftxui::Button("Search", [&] {
            inputValue = input;
            input.clear();
            screen.PostEvent(ftxui::Event::Custom);  
        }),
        ftxui::Button("Back", screen.ExitLoopClosure())
    });

    auto renderer = ftxui::Renderer(form, [&] {
        std::vector<ftxui::Element> elements;

        elements.push_back(ftxui::text("Search by semester") | ftxui::bold | ftxui::center);
        elements.push_back(ftxui::separator());
        elements.push_back(form->Render());

        if (!inputValue.empty()) {
            int count = 0;
            Student* result = handler.listByCriteria(
                [&](const Student& s) {
                    try {
                        return s.getSemester() <= std::stoi(inputValue);
                    }
                    catch(const std::invalid_argument&) {
                        return false;
                    }

                },
                count
            );

            list_elems.clear();

            elements.push_back(ftxui::separator());

            if (count == 0 || result == nullptr) {
                elements.push_back(ftxui::text("No matching students found."));
            } else {
                for (int i = 0; i < count; ++i) {
                    const Student& s = result[i];
                    std::string line = "ID: " + std::to_string(s.getId()) + " " +
                                       s.getFirstName() + " " + s.getLastName() +
                                       " Semester: " + std::to_string(s.getSemester()) +
                                       " Avg: " + std::to_string(s.getAverage());
                    elements.push_back(ftxui::text(line));
                }
                delete[] result;
            }

            inputValue.clear();
        }

        return ftxui::vbox(std::move(elements)) | ftxui::border;
    });

    screen.Loop(renderer);
}

void TUI::showNth(ftxui::ScreenInteractive& screen) {
    std::string input;
    std::string error_message;
    std::string result_line;

    auto form = ftxui::Container::Vertical({
        ftxui::Input(&input, "Enter index"),
        ftxui::Button("Search", [&] {
            try {
                int index = std::stoi(input);
                Student s = handler.getByIdx(index);

                if (s.getId() == -1) {
                    result_line = "Error: Index Out Of Range";
                } else {
                    result_line = "ID: " + std::to_string(s.getId()) + " " +
                                  s.getFirstName() + " " + s.getLastName() +
                                  " Semester: " + std::to_string(s.getSemester()) +
                                  " Avg: " + std::to_string(s.getAverage());
                }
                error_message.clear();
            } catch (const std::exception& e) {
                error_message = "Invalid input. Please enter a valid number.";
                result_line.clear();  
            }

            input.clear();
            screen.PostEvent(ftxui::Event::Custom); 
        }),
        ftxui::Button("Back", screen.ExitLoopClosure())
    });

    auto renderer = ftxui::Renderer(form, [&] {
        std::vector<ftxui::Element> elements;
        elements.push_back(ftxui::text("Search by Index") | ftxui::bold | ftxui::center);
        elements.push_back(ftxui::separator());
        elements.push_back(form->Render());

        if (!error_message.empty()) {
            elements.push_back(ftxui::separator());
            elements.push_back(ftxui::text(error_message) | ftxui::color(ftxui::Color::Red));
        }

        if (!result_line.empty()) {
            elements.push_back(ftxui::separator());
            elements.push_back(ftxui::text(result_line));
        }

        return ftxui::vbox(std::move(elements)) | ftxui::border;
    });

    screen.Loop(renderer);
}

void TUI::showNtoK(ftxui::ScreenInteractive& screen) {
    std::string input1, input2;

    std::vector<ftxui::Component> list_elems;

    auto form = ftxui::Container::Vertical({
        ftxui::Input(&input1, "Enter start index"),
        ftxui::Input(&input2, "Enter end index"),
        ftxui::Button("Search", [&] {
            inputValue = input1 + ";" + input2;
            input1.clear();
            input2.clear();
            screen.PostEvent(ftxui::Event::Custom);  
        }),
        ftxui::Button("Back", screen.ExitLoopClosure())
    });

    auto renderer = ftxui::Renderer(form, [&] {
        std::vector<ftxui::Element> elements;

        elements.push_back(ftxui::text("Search by index brackets") | ftxui::bold | ftxui::center);
        elements.push_back(ftxui::separator());
        elements.push_back(form->Render());

        if (!inputValue.empty()) {
            int count = 0;
            size_t pos = inputValue.find(";");
            int n = std::stoi(inputValue.substr(0, pos));
            int k = std::stoi(inputValue.substr(pos + 1));

            Student* result = handler.getFromNtoK(n,k,count);

            list_elems.clear();

            elements.push_back(ftxui::separator());

            if (count == 0 || result == nullptr) {
                elements.push_back(ftxui::text("No matching students found."));
            } else {
                for (int i = 0; i < count; ++i) {
                    const Student& s = result[i];
                    std::string line = "ID: " + std::to_string(s.getId()) + " " +
                                       s.getFirstName() + " " + s.getLastName() +
                                       " Semester: " + std::to_string(s.getSemester()) +
                                       " Avg: " + std::to_string(s.getAverage());
                    elements.push_back(ftxui::text(line));
                }
                delete[] result;
            }

            inputValue.clear();
        }

        return ftxui::vbox(std::move(elements)) | ftxui::border;
    });

    screen.Loop(renderer);
}

void TUI::showByFullName(ftxui::ScreenInteractive& screen) {
    std::string input1, input2;

    std::vector<ftxui::Component> list_elems;

    auto form = ftxui::Container::Vertical({
        ftxui::Input(&input1, "Enter Firstname"),
        ftxui::Input(&input2, "Enter Lastname"),

        ftxui::Button("Search", [&] {
            inputValue = input1 + input2;
            input1.clear();
            input2.clear();
            screen.PostEvent(ftxui::Event::Custom);  
        }),
        ftxui::Button("Back", screen.ExitLoopClosure())
    });

    auto renderer = ftxui::Renderer(form, [&] {
        std::vector<ftxui::Element> elements;

        elements.push_back(ftxui::text("Search by semester") | ftxui::bold | ftxui::center);
        elements.push_back(ftxui::separator());
        elements.push_back(form->Render());

        if (!inputValue.empty()) {
            int count = 0;
            Student* result = handler.listByCriteria(
                [&](const Student& s) {
                    try {
                        return s.getFirstName() + s.getLastName() == inputValue;
                    }
                    catch(const std::invalid_argument&) {
                        return false;
                    }

                },
                count
            );

            list_elems.clear();

            elements.push_back(ftxui::separator());

            if (count == 0 || result == nullptr) {
                elements.push_back(ftxui::text("No matching students found."));
            } else {
                for (int i = 0; i < count; ++i) {
                    const Student& s = result[i];
                    std::string line = "ID: " + std::to_string(s.getId()) + " " +
                                       s.getFirstName() + " " + s.getLastName() +
                                       " Semester: " + std::to_string(s.getSemester()) +
                                       " Avg: " + std::to_string(s.getAverage());
                    elements.push_back(ftxui::text(line));
                }
                delete[] result;
            }

            inputValue.clear();
        }

        return ftxui::vbox(std::move(elements)) | ftxui::border;
    });

    screen.Loop(renderer);
}

void TUI::showAvgByGivenSemester(ftxui::ScreenInteractive& screen) {
    std::string input;
    std::string error_message;
    std::string result_line;

    auto form = ftxui::Container::Vertical({
        ftxui::Input(&input, "Enter semester"),
        ftxui::Button("Search", [&] {
            try {
                int semester = std::stoi(input);
                double avg = this->handler.getAverageOfSemester(semester);

                if (avg == 0.0) {
                    result_line = "Missing info about given semester";
                } else {
                    result_line = "Semester " + std::to_string(semester) +
                                  " average: " + std::to_string(avg);
                }

                error_message.clear();
            } catch (const std::exception& e) {
                error_message = "Invalid input. Please enter a number.";
                result_line.clear();
            }

            input.clear();
            screen.PostEvent(ftxui::Event::Custom);  
        }),
        ftxui::Button("Back", screen.ExitLoopClosure())
    });

    auto renderer = ftxui::Renderer(form, [&] {
        std::vector<ftxui::Element> elements;

        elements.push_back(ftxui::text("Search by Semester") | ftxui::bold | ftxui::center);
        elements.push_back(ftxui::separator());
        elements.push_back(form->Render());

        if (!error_message.empty()) {
            elements.push_back(ftxui::separator());
            elements.push_back(ftxui::text(error_message) | ftxui::color(ftxui::Color::Red));
        }

        if (!result_line.empty()) {
            elements.push_back(ftxui::separator());
            elements.push_back(ftxui::text(result_line));
        }

        return ftxui::vbox(std::move(elements)) | ftxui::border;
    });

    screen.Loop(renderer);
}

void TUI::showOverallAverage(ftxui::ScreenInteractive& screen) {
    double avg = handler.getOverallAverage();
    std::string avg_text = "Average: " + std::to_string(avg);

    auto back_button = ftxui::Button("Back", screen.ExitLoopClosure());

    auto container = ftxui::Container::Vertical({
        back_button
    });

    auto renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
            ftxui::text("Average: ") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            ftxui::text(avg_text) | ftxui::center,
            ftxui::separator(),
            back_button->Render()
        }) | ftxui::border;
    });

    screen.Loop(renderer);
}

void TUI::showSize(ftxui::ScreenInteractive& screen) {
    double size = handler.getOverallAverage();
    std::string size_text = "Average: " + std::to_string(size);

    auto back_button = ftxui::Button("Back", screen.ExitLoopClosure());

    auto container = ftxui::Container::Vertical({
        back_button
    });

    auto renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
            ftxui::text("Size: ") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            ftxui::text(size_text) | ftxui::center,
            ftxui::separator(),
            back_button->Render()
        }) | ftxui::border;
    });

    screen.Loop(renderer);
}

TUI::TUI(Handler& handlerRef) : handler(handlerRef) {
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
        "Get By Firstname",
        "Get By Lastname",
        "Get all above given average",
        "Get all below given average",
        "Get all above given semester",
        "Get all below given semester",
        "Save To File",
        "Load From File",
        "Save To Binary File",
        "Load From Binary File",
        "Show nth",
        "Show from n to k",
        "Get By fullname",
        "Average by semester",
        "Overall average",
        "Get size of dataset"
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
                case 0:  showAddForm(screen); break;
                case 1:  showRemoveForm(screen); break;
                case 2:  showList(screen); break;
                case 3:  showUpdateForm(screen); break;
                case 4:  showAvgBySemester(screen); break;
                case 5:  showBestStudent(screen); break;
                case 6:  showByFirstname(screen); break;
                case 7:  showByLastname(screen); break;
                case 8:  showAboveAverage(screen); break;
                case 9:  showBelowAverage(screen); break;
                case 10: showAboveSemester(screen); break;
                case 11: showBelowSemester(screen); break;
                case 12: 
                    if (handler.saveToFile())
                        info_message = "Data saved to file.";
                    else
                        info_message = "Failed to save data.";
                    break;
                case 13:
                    if (handler.loadFromFile())
                        info_message = "Data loaded from file.";
                    else
                        info_message = "Failed to load data.";
                    break;
                case 14:
                    if (handler.saveToBinary())
                        info_message = "Binary file saved.";
                    else
                        info_message = "Failed to save binary file.";
                    break;
                case 15:
                    if (handler.loadFromBinary())
                        info_message = "Binary file loaded.";
                    else
                        info_message = "Failed to load binary file.";
                    break;
                case 16: showNth(screen); break;
                case 17: showNtoK(screen); break;
                case 18: showByFullName(screen); break;
                case 19: showAvgByGivenSemester(screen); break;
                case 20: showOverallAverage(screen); break;
                case 21: showSize(screen); break;
                case 22:
                    screen.Exit();
                    break;
                default:
                    info_message = "Unknown option selected.";
            }
            return true;
        }
        return false;
    }));
}
