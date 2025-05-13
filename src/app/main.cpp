#include "tui.h"
#include "handler.h"

int main() {
    try {
        Handler handler;
        TUI tui(handler);
    } catch (const std::system_error& e) {
        std::cerr << "System error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
}