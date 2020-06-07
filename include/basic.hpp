#pragma once
#ifndef __BASIC_H__
#define __BASIC_H__

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "escaper.hpp"
#include "fancy.hpp"
#include "jute.h"

namespace wei {

    using std::cin;
    using std::cout;
    using std::ifstream;
    using std::setw;
    using std::string;
    using std::vector;

    using namespace escaper;
    using fancy::Attribute;
    using fancy::detail::fancy_str;

    using select_options = vector<string>;

    namespace symbols {

#if IS_WINDOWS
        const string RADIO_ON = "(*)";
        const string RADIO_OFF = "( )";
#else
        const string RADIO_ON = "◉";
        const string RADIO_OFF = "◯";
#endif
        const string POINT_RIGHT = "☞";
        const string ARROW_RIGHT = "❯";
        const string QUESTION_MARK = "?";

    }  // namespace symbols

    namespace detail {

        string highlight_str(const string& text) {
            return fancy_str(text, Attribute::Reset, Attribute::Cyan);
        }

        string question_str(const string& text) {
            return highlight_str(symbols::QUESTION_MARK) + " " + text + " " +
                   symbols::ARROW_RIGHT + " ";
        }

        string answer_str(const string& text) {
            return highlight_str(symbols::ARROW_RIGHT) + " " + text;
        }

        bool is_valid_str(char c) { return c >= '0' && c <= 'z'; }

    }  // namespace detail
}


#endif //__BASIC_H__
