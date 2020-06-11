#pragma once
#ifndef __UTILS_H__
#define __UTILS_H__

#include "basic.hpp"
#include "jute.h"

// Enable VTMode on windows
// https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
#if IS_WINDOWS
inline bool EnableVTMode() {
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
inline bool HandleConsole() {
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
inline bool HandleConsole() { return true; }
#endif

inline wei::Poems loadData() {
    std::ifstream in("shijing.json");
    std::string str = "";
    std::string tmp;
    while (getline(in, tmp)) str += tmp;
    jute::jValue v = jute::parser::parse(std::move(str));

    wei::Poems poems;
    poems.reserve(v.size());

    for (size_t i = 0; i < v.size(); i++) {
        Poem poem = Poem::create(v[i]);
        poems.push_back(std::move(poem));
    }
    return poems;
}

#endif  // __UTILS_H__
