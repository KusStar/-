#pragma once
#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "basic.hpp"

namespace wei {
    namespace impls {
        void search(jute::jValue& v) {
            string result;

            cout << detail::question_str("搜索");

            select_options poems;

            size_t len = poems.size();

            int index = 0;

            int offset = 0;

            auto mark = [&](int current, int index) -> string {
                return current == index
                           ? detail::highlight_str(symbols::RADIO_ON)
                           : symbols::RADIO_OFF;
            };

            // 匹配诗词
            auto search_poem = [&]() {
                auto cur = v[offset];
                string title = cur["title"].as_string();
                poems.push_back(title);
            };

            auto draw = [&](char c) {
                cout << static_cast<char>(c);
                cout << "\n";

                len = poems.size();

                for (int i = 0; i < len; i++) {
                    string cur_str = mark(index, i) + " " + poems.at(i);
                    cout << cur_str << "\n";
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
                            search_poem();
                            len -= 2;
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
                                break;
                            case KEY_DOWN_ARROW:
                            case KEY_RIGHT_ARROW:
                                index += 1;
                                if (index > len - 1)
                                    index = 0;
                                c = 0;
                                break;
                        }
                        draw(c);
                        break;
                    default:
                        if (detail::is_valid_str(c)) {
                            result += c;
                            search_poem();
                        }
                        draw(c);
                        break;
                }
            }

        end:
            cout << cursor::left << cursor::down(100);
            cout << index;
        }

    }  // namespace impls

}  // namespace wei

#endif // __SEARCH_H__
