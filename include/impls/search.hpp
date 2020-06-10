#pragma once
#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "basic.hpp"

namespace wei {
    namespace impls {
        void show(const Poems&, const size_t);

        inline void search(const Poems& poems) {
            cout << detail::question_str("搜索");

            string result;
            std::vector<size_t> matched;
            size_t len = 0;

            // 当前选择条目
            int selected_index = 0;
            // 当前偏远量，用于分页
            int offset = 0;

            auto mark = [&](size_t current, size_t index) -> string {
                return current == index
                           ? detail::highlight_str(symbols::RADIO_ON)
                           : symbols::RADIO_OFF;
            };

            auto get_current_poem_index = [&](size_t i) {
                return matched[i + offset * 5];
            };

            // 匹配诗词
            auto search_poem = [&]() {
                matched.clear();
                matched.shrink_to_fit();

                if (result.size() <= 0)
                    return;

                for (size_t i = 0; i < poems.size(); i++) {
                    auto is_title_matched =
                        poems[i].pinyin_title.find(result) != string::npos;

                    auto is_content_matched =
                        poems[i].pinyin_content.find(result) != string::npos;

                    if (is_title_matched || is_content_matched) {
                        matched.push_back(i);
                    }
                }
            };

            auto draw = [&](char c) {
                const auto temp_len = matched.size() - offset * 5;

                if (temp_len < len) {
                    cout << cursor::down(len + 1) << erase::lines(len + 1);
                    cout << cursor::left << cursor::forward(8 + result.size());
                }

                cout << static_cast<char>(c);
                cout << "\n";

                len = temp_len > 5 ? 5 : temp_len;

                for (size_t i = 0; i < len; i++) {
                    auto cur_index = get_current_poem_index(i);
                    auto poem = poems[cur_index];
                    const string title = poem.title + symbols::DOT +
                                         poem.chapter + symbols::DOT +
                                         poem.section;

                    string cur_str = mark(selected_index, i) + " " + title;

                    cout << erase::line << cur_str << "\n";
                }

                cout << erase::line;
                cout << detail::highlight_str(">") << " ";
                cout << std::left << std::setw(10)
                     << detail::compose_str(offset + 1, " / ",
                                            matched.size() / 5 + 1);
                cout << "共" << matched.size() << "条"
                     << "\n ";

                cout << cursor::up(len + 2);
                cout << cursor::left << cursor::forward(9 + result.size());
            };

            for (;;) {
                auto c = getch();
                switch (c) {
                    case KEY_BACKSPACE:
                        if (result.size() > 0) {
                            cout << "\b \b";
                            offset = 0;
                            result.erase(result.end() - 1, result.end());
                            search_poem();
                            draw(c);
                        }
                        break;
                    case KEY_SPACE:
                        cout << " ";
                        result += " ";
                        break;
                    case KEY_ENTER:
                        cout << cursor::down(len) << "\n";
                        // 进入 show()
                        show(poems, get_current_poem_index(selected_index));
                        // 退出后重新进入搜索
                        return search(poems);
                    case KEY_ESC:
                        cout << cursor::down(len + 2) << erase::lines(len + 2);
                        return;
                    case KEY_SPEC:
                        switch (c = getch()) {
                            case KEY_UP_ARROW:
                                selected_index -= 1;
                                if (selected_index < 0)
                                    selected_index = len - 1;
                                break;
                            case KEY_DOWN_ARROW:
                                selected_index += 1;
                                if (selected_index > len - 1)
                                    selected_index = 0;
                                break;
                            case KEY_LEFT_ARROW:
                                offset -= 1;
                                if (offset < 0) {
                                    offset = matched.size() / 5;
                                }
                                break;
                            case KEY_RIGHT_ARROW:
                                offset += 1;
                                if (offset > matched.size() / 5) {
                                    offset = 0;
                                }
                                break;
                        }
                        c = 0;
                        draw(c);
                        break;
                    default:
                        if (detail::is_valid_str(c)) {
                            result += c;
                            offset = 0;
                            search_poem();
                        }
                        draw(c);
                        break;
                }
            }
        }

    }  // namespace impls

}  // namespace wei

#endif  // __SEARCH_H__
