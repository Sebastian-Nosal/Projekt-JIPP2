cmake_minimum_required(VERSION 3.20)
project(JiPP_project)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    GIT_TAG main
)
FetchContent_MakeAvailable(ftxui)

enable_testing()
find_package(GTest REQUIRED)

add_library(JiPP_project_smartArray INTERFACE)

target_include_directories(JiPP_project_smartArray INTERFACE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/smartArray
)

add_executable(JiPP_project_app
    src/app/main.cpp
    src/app/tui.cpp
    src/app/handler.cpp
    src/app/data.cpp
)

target_link_libraries(JiPP_project_app
    JiPP_project_smartArray
    ftxui::screen
    ftxui::dom
    ftxui::component
)

add_executable(SmartArrayTest
    tests/test_SmartArray.cpp
)

target_link_libraries(SmartArrayTest
    JiPP_project_smartArray
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(SmartArrayTest)