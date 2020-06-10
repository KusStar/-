#pragma once
#ifndef __SHOW_H__
#define __SHOW_H__

#include "basic.hpp"

namespace wei {
    namespace impls {

        inline void explore(const Poems& poems, const size_t default_index = 0) {
            cout << "\n";
            Brush brush;

            const int max_index = poems.size() - 1;

            int offset = static_cast<int>(default_index);
            // 打印 offset 对应的诗, 并返回需要的行数
            auto prepare = [&]() {
                auto poem = poems[offset];

                detail::brush_fill_poem(brush, poem, offset);

                brush << "\n";
            };

            for (;;) {
                prepare();

                brush.draw();

                auto c = getch();

                switch (c) {
                    case KEY_ESC:
                        cout << "\n";
                        return;
                    case KEY_SPEC:
                        switch (c = getch()) {
                            case KEY_UP_ARROW:
                                c = 'h';
                                break;
                            case KEY_DOWN_ARROW:
                                c = 'l';
                                break;
                            case KEY_LEFT_ARROW:
                                c = 'j';
                                break;
                            case KEY_RIGHT_ARROW:
                                c = 'k';
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
                brush.flush();
            }
        }

    }  // namespace impls

}  // namespace wei

#endif  // __SHOW_H__
