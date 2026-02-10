#include <locale>
inline void setRussianLocale() {
    try {
        #ifdef _WIN32
            setlocale(LC_ALL, "ru_RU.UTF-8");
            std::locale::global(std::locale("ru_RU.UTF-8"));
        #else
            setlocale(LC_ALL, "ru_RU.utf-8");
            std::locale::global(std::locale("ru_RU.utf-8"));
        #endif
    }
    catch (const std::exception& e) {
        try {
            setlocale(LC_ALL, "C.UTF-8");
            std::locale::global(std::locale("C.UTF-8"));
        }
        catch (...) {
        }
    }
}