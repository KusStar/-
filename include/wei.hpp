#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "escaper.hpp"
#include "fancy.hpp"

#define APP_NAME "薇"
#define APP_VERSION "0.1.0"

namespace wei {

    using namespace std;
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

        size_t utf8Len(string s) {
            return count_if(s.begin(), s.end(), [](char c) {
                return (static_cast<unsigned char>(c) & 0xC0) != 0x80;
            });
        }

        bool is_valid_str(char c) { return c >= '0' && c <= 'z'; }

    }  // namespace detail

    string prompt(const string& message = "Default") {
        string result;

        cout << detail::question_str(message);
        getline(cin, result);

        return result;
    }

    void search() {
        string result;

        cout << detail::question_str("搜索");

        select_options options = {"采薇", "关雎", "卷耳"};

        int len = options.size();
        int index = 0;

        auto mark = [&](int current, int index) -> string {
            return current == index ? detail::highlight_str(symbols::RADIO_ON)
                                    : symbols::RADIO_OFF;
        };

        auto draw = [&](char c) {
            cout << static_cast<char>(c);
            cout << "\n";

            for (int i = 0; i < len; i++) {
                string option_str = mark(index, i) + " " + options.at(i);
                cout << option_str << "\n";
            }

            cout << cursor::up(len + 1) << cursor::forward(9 + result.size());
        };

        for (;;) {
            auto c = getch();
            switch (c) {
                case KEY_BACKSPACE:
                    if (result.size() > 0) {
                        cout << "\b \b";
                        result.erase(result.end() - 1, result.end());
                        draw(c);
                    }
                    break;
                case KEY_SPACE:
                    cout << " ";
                    result += " ";
                    break;
                case KEY_ENTER:
                case KEY_ESC:
                    goto end;
                    break;
                case KEY_SPEC:
                    switch (c = getch()) {
                        case KEY_UP_ARROW:
                        case KEY_LEFT_ARROW:
                            index -= 1;
                            if (index < 0)
                                index = len - 1;
                            c = 0;
                            draw(c);
                            break;
                        case KEY_DOWN_ARROW:
                        case KEY_RIGHT_ARROW:
                            index += 1;
                            if (index > len - 1)
                                index = 0;
                            c = 0;
                            draw(c);
                            break;
                    }
                    break;
                default:
                    if (detail::is_valid_str(c)) {
                        result += c;
                        draw(c);
                    }
                    break;
            }
        }

    end:
        cout << cursor::left << cursor::down(100);
        cout << index;
    }

    string select(const string& message, const select_options& options) {
        auto mark = [&](int current, int index) -> string {
            return current == index ? detail::highlight_str(symbols::RADIO_ON)
                                    : symbols::RADIO_OFF;
        };

        int index = 0;
        int len = options.size();

        cout << detail::question_str(message) << "\n";

        for (;;) {
            for (int i = 0; i < len; i++) {
                string option_str = mark(index, i) + " " + options.at(i);
                cout << option_str << "\n";
            }

            int c = getch();

            switch (c) {
                case KEY_ENTER:
                case KEY_SPACE:
                    return options.at(index);
                    break;
                case KEY_SPEC:
                    switch (c = getch()) {
                        case KEY_UP_ARROW:
                        case KEY_LEFT_ARROW:
                            c = 'h';
                            break;
                        case KEY_DOWN_ARROW:
                        case KEY_RIGHT_ARROW:
                            c = 'l';
                            break;
                    }
                default:
                    switch (c) {
                        case 'h':
                        case 'j':
                            index -= 1;
                            if (index < 0)
                                index = len - 1;
                            break;
                        case 'k':
                        case 'l':
                            index += 1;
                            if (index > len - 1)
                                index = 0;
                            break;
                        case 'q':
                            cout << cursor::show;
                            cout << "\n";
                            return options.at(len - 1);
                    }
                    break;
            }
            cout << erase::lines(len);
        }
    }

}  // namespace wei
