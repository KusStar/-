#pragma once
#ifndef __BRUSH_H__
#define __BRUSH_H__

#include <string>
#include <vector>

#include "escaper.hpp"

class Brush {
public:
    Brush() = default;

    ~Brush() { clear(); }

    void draw() { std::cout << oss_.str(); }

    void flush() {
        std::cout << escaper::erase::lines(lines());
        clear();
    }

    int lines() {
        int n = 0;
        const std::string content = oss_.str();

        size_t pos = content.find("\n");
        while (pos != std::string::npos) {
            pos = content.find("\n", pos + 1);
            n++;
        }

        return n;
    }

    void clear() {
        oss_.str("");
        oss_.clear();
    }

    template <class T>
    Brush& operator<<(const T& t) {
        oss_ << t;
        return *this;
    }

private:
    std::ostringstream oss_;
};

#endif  // __BRUSH_H__
