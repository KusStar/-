#pragma once
#ifndef __HELP_H
#define __HELP_H

#include "basic.hpp"

namespace wei {
    namespace impls {

        inline void help() {
            cout << "\n";
            cout << "操作指南"
                 << "\n";
            cout << "按 q 返回上一页";

            for (;;) {
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
                            case 'j':
                                cout << scroll::down();
                                break;
                            case 'k':
                                cout << scroll::up();
                                break;
                            case 'h':
                                cout << cursor::backward();
                                break;
                            case 'l':
                                cout << cursor::forward();
                                break;
                            case 'q':
                                cout << "\n";
                                return;
                        }
                        break;
                }
            }
        }

    }  // namespace impls

}  // namespace wei

#endif  // __HELP_H
