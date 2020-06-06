#ifndef __WEI_H__
#define __WEI_H__

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <iomanip>

#include "escaper.hpp"
#include "fancy.hpp"
#include "jute.h"

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

        size_t utf8Len(string s) {
            return count_if(s.begin(), s.end(), [](char c) {
                return (static_cast<unsigned char>(c) & 0xC0) != 0x80;
            });
        }

        bool is_valid_str(char c) { return c >= '0' && c <= 'z'; }

    }  // namespace detail

    namespace impls {
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
                return current == index
                           ? detail::highlight_str(symbols::RADIO_ON)
                           : symbols::RADIO_OFF;
            };

            auto draw = [&](char c) {
                cout << static_cast<char>(c);
                cout << "\n";

                for (int i = 0; i < len; i++) {
                    string option_str = mark(index, i) + " " + options.at(i);
                    cout << option_str << "\n";
                }

                cout << cursor::up(len + 1)
                     << cursor::forward(9 + result.size());
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
                return current == index
                           ? detail::highlight_str(symbols::RADIO_ON)
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

        void show_all(jute::jValue& v) {
            cout << "\n";

            const int max = v.size() - 1;
            int offset = 0;
            fancy::Fancy f;
            // 打印 offset 对应的诗, 并返回需要的行数
            auto draw = [&]() {
                int len = 0;
                auto cur = v[offset];
                cout << erase::line_end;
                cout << "\n\n";
                cout << setw(10) << " ";
                cout << (f | Attribute::Cyan);
                cout << "  [" << offset + 1 << "] ";

                cout << (f | Attribute::Yellow);
                cout << cur["title"].as_string();
                cout << "·" << cur["chapter"].as_string();
                cout << "·" << cur["section"].as_string();
                cout << fancy::ending;
                cout << "\n\n";
                len += 4;

                for (int j = 0; j < cur["content"].size(); j++) {
                    cout << setw(5) << " ";
                    cout << cur["content"][j].as_string() << "\n\n";
                    len += 2;
                }
                cout << "\n";
                len += 1;

                return len;
            };

            for (;;) {
                auto len = draw();

                auto c = getch();
                switch (c) {
                    case KEY_SPEC:
                        switch (c = getch()) {
                            case KEY_UP_ARROW:
                                c = 'j';
                                break;
                            case KEY_DOWN_ARROW:
                                c = 'k';
                                break;
                            case KEY_LEFT_ARROW:
                                c = 'h';
                                break;
                            case KEY_RIGHT_ARROW:
                                c = 'l';
                                break;
                        }
                    default:
                        switch (c) {
                            case 'k':
                                offset += 1;
                                if (offset > max) {
                                    offset = 0;
                                }
                                break;
                            case 'j':
                                offset -= 1;
                                if (offset < 0) {
                                    offset = max;
                                }
                                break;
                            case 'h':
                                offset = offset - 10 < 0 ? offset + max - 10
                                                         : offset - 10;
                                break;
                            case 'l':
                                offset = offset + 10 > max ? offset + 10 - max
                                                           : offset + 10;
                                break;
                            case 'q':
                                cout << cursor::show;
                                cout << "\n";
                                return;
                        }
                        break;
                }

                // 根据 len 来清除终端文字，以便显示下一首
                cout << erase::lines(len);
            }
        }

        void help() {
            cout << "\n";
            cout << "操作指南"
                 << "\n";
            cout << "按 q 返回上一页";
            cout << "\n";
            cout << cursor::hide;

            for (;;) {
                auto c = getch();
                switch (c) {
                    case KEY_SPEC:
                        switch (c = getch()) {
                            case KEY_UP_ARROW:
                                cout << scroll::down();
                                break;
                            case KEY_DOWN_ARROW:
                                cout << scroll::up();
                                break;
                        }
                        break;
                    default:
                        if (c == 'q') {
                            cout << cursor::show;
                            cout << "\n";
                            return;
                        }
                        break;
                }
            }
        }

        jute::jValue loadData() {
            ifstream in("shijing.json");
            string str = "";
            string tmp;
            while (getline(in, tmp)) str += tmp;
            return jute::parser::parse(str);
        }

    }  // namespace impls

}  // namespace wei

#endif  // __WEI_H__
