#pragma once
#ifndef __SHOW_H__
#define __SHOW_H__

#include "basic.hpp"

namespace wei {
    namespace impls {
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

    }  // namespace impls

}  // namespace wei

#endif // __SHOW_H__
