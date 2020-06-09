#pragma once
#ifndef __SHOW_H__
#define __SHOW_H__

#include "basic.hpp"

namespace wei {
    namespace impls {

        inline void show(const Poems& poems) {
            cout << "\n";

            const int max_index = poems.size() - 1;

            int offset = 0;
            // 打印 offset 对应的诗, 并返回需要的行数
            auto draw = [&]() {
                size_t len = 0;
                auto cur = poems[offset];
                detail::draw_poem(cur, len, offset);
                cout << "\n";
                len += 1;

                return len;
            };

            for (;;) {
                auto len = draw();

                auto c = getch();
                switch (c) {
                    case KEY_ESC:
                        cout << "\n";
                        return;
                        break;
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
                                if (offset > max_index) {
                                    offset = 0;
                                }
                                break;
                            case 'j':
                                offset -= 1;
                                if (offset < 0) {
                                    offset = max_index;
                                }
                                break;
                            case 'h':
                                offset = offset - 10 < 0
                                             ? offset + max_index - 10
                                             : offset - 10;
                                break;
                            case 'l':
                                offset = offset + 10 > max_index
                                             ? offset + 10 - max_index
                                             : offset + 10;
                                break;
                            case 'q':
                                cout << "\n";
                                return;
                        }
                        break;
                }

                // 根据 len 来清除终端文字，以便显示下一首
                cout << erase::lines(len);
            }
        }

    }  // namespace impls

}  // namespace wei

#endif  // __SHOW_H__
