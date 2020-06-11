#pragma once
#ifndef __BASIC_H__
#define __BASIC_H__

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "class/brush.hpp"
#include "class/poem.hpp"
#include "class/reader.hpp"
#include "class/writer.hpp"
#include "escaper.hpp"
#include "fancy.hpp"
#include "jute.h"

namespace wei {

    using std::cout;
    using std::size_t;
    using std::string;

    using namespace escaper;
    using fancy::Attribute;
    using fancy::detail::fancy_str;

    using select_options = std::vector<string>;

    using Poems = std::vector<Poem>;

    namespace constants {
        const string APP_NAME = "薇";
        const string APP_VERSION = "0.1.0";

        const string EXPLORE = "探索";
        const string SEARCH = "搜索";
        const string HISTORY = "历史";
        const string HELP = "帮助";
        const string ABOUT = "关于";
        const string QUIT = "退出";


    }  // namespace constants
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
        const string DOT = "·";
        const string APP_ICON = "✾";
        const string SEARCH_ICON = "⚘";

    }  // namespace symbols

    namespace detail {

        inline string highlight_str(const string& text) {
            return fancy_str(text, Attribute::Reset, Attribute::Cyan);
        }

        inline string bright_str(const string& text,
                                 Attribute color = Attribute::Yellow) {
            return fancy_str(text, color, Attribute::Bright);
        }

        inline string title_str(const string& text,
                                const string& symbol = symbols::QUESTION_MARK) {
            return highlight_str(symbol) + " " + text + " " +
                   symbols::ARROW_RIGHT + " ";
        }

        inline string answer_str(const string& text) {
            return highlight_str(symbols::ARROW_RIGHT) + " " + text;
        }

        inline string mark_str(int current, int index) {
            return current == index ? detail::highlight_str(symbols::RADIO_ON)
                                    : symbols::RADIO_OFF;
        };

        inline bool is_valid_str(char c) { return c >= '0' && c <= 'z'; }

        template <typename... Arg>
        inline string compose_str(const Arg&... arg) {
            std::ostringstream os;
            using List = int[];
            (void)List{0, (os << arg, 0)...};
            return os.str();
        }

        inline void brush_fill_poem(Brush& brush, const Poem& poem,
                                    int offset) {
            brush << "\n\n ";
            brush << fancy_str(detail::compose_str("  [", offset + 1, "] "),
                               Attribute::Reset, Attribute::Cyan);

            brush << fancy_str(poem.title + symbols::DOT + poem.chapter +
                                   symbols::DOT + poem.section,
                               Attribute::Reset, Attribute::Yellow);

            brush << "\n\n";

            for (auto line : poem.content) {
                brush << " " << line << "\n\n";
            }
        }

    }  // namespace detail

}  // namespace wei

#endif  //__BASIC_H__
