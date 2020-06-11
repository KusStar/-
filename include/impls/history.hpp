#pragma once
#ifndef __HISTORY_H
#define __HISTORY_H

#include "basic.hpp"

namespace wei {
    namespace impls {

        inline void history(const Poems& poems) {
            Brush brush;
            Reader reader;

            auto items = reader.get_all();

            cout << '\n'
                 << detail::title_str(constants::HISTORY, symbols::POINT_RIGHT)
                 << '\n';

            int offset = 0;
            int index = 0;
            int len = 0;

            auto go_to_explore = [&]() {
                if (items.size() <= 0)
                    return;
                auto target_index = index + offset * 5;
                auto poem_index = items[target_index].index;
                // do nothing iff target_index is invalid
                if (poem_index >= poems.size()) {
                    return;
                }

                explore(poems, poem_index);
            };

            for (;;) {
                const auto temp_len = items.size() - offset * 5;

                len = temp_len > 5 ? 5 : temp_len;
                for (size_t i = 0; i < len; i++) {
                    auto target_index = i + offset * 5;

                    brush << detail::mark_str(index, i) + " " +
                                 items.at(target_index).title
                          << "\n";
                }

                if (items.size() > 0) {
                    brush << detail::highlight_str(">") << " ";
                    brush << detail::compose_str(offset + 1, " / ",
                                                 items.size() / 5 + 1);
                    brush << "  共" << items.size() << "条" << '\n';
                } else {
                    brush << "< 记录为空" << '\n';
                }

                brush.draw();

                auto c = getch();
                switch (c) {
                    case KEY_SPACE:
                    case KEY_ENTER:
                        go_to_explore();
                        break;
                    case KEY_ESC:
                        c = 'q';
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
                            case 'j':
                                index -= 1;
                                if (index < 0)
                                    index = len - 1;
                                break;
                            case 'k':
                                index += 1;
                                if (index > len - 1)
                                    index = 0;
                                break;
                            case 'h':
                                offset -= 1;
                                if (offset < 0) {
                                    offset = items.size() / 5;
                                }
                                index = 0;
                                break;
                            case 'l':
                                offset += 1;
                                if (offset > items.size() / 5) {
                                    offset = 0;
                                }
                                index = 0;
                                break;
                            case 'x':
                                items.clear();
                                items.shrink_to_fit();
                                reader.clear();
                                len = 0;
                                break;
                            case 'q':
                                cout << "\n";
                                return;
                        }
                        break;
                }
                brush.flush();
                cout << erase::line;
            }
        }
    }  // namespace impls

}  // namespace wei

#endif  // __HISTORY_H
