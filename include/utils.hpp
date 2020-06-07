#pragma once
#ifndef __UTILS_H__
#define __UTILS_H__

#include "jute.h"

#include "escaper.hpp"

#define APP_NAME "薇"
#define APP_VERSION "0.1.0"

// Enable VTMode on windows
// https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
#if IS_WINDOWS
bool EnableVTMode() {
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        return false;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        return false;
    }
    return true;
}
bool HandleConsole() {
    bool fSuccess = EnableVTMode();
    if (!fSuccess) {
        std::cout << "Unable to enter VT processing mode. Quitting."
                  << "\n";
        return false;
    }
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        std::cout << "Couldn't get the console handle. Quitting."
                  << "\n";
        return false;
    }
    return true;
}
#else
bool HandleConsole() { return true; }
#endif

jute::jValue loadData() {
    std::ifstream in("shijing.json");
    std::string str = "";
    std::string tmp;
    while (getline(in, tmp)) str += tmp;
    return jute::parser::parse(str);
}

#endif // __UTILS_H__
