#pragma once
#ifndef __ABOUT_H
#define __ABOUT_H

#include "basic.hpp"

namespace wei {
    namespace impls {

        inline void about() {
            using namespace constants;
            using namespace symbols;
            cout << "\n";
            const std::vector<string> infos = {
                "© [" + APP_NAME + "] v" + APP_VERSION,
                RADIO_OFF + " 开发成员",
                RADIO_ON + " " + MEMBERS[0],
                RADIO_ON + " " + MEMBERS[1],
                RADIO_ON + " " + MEMBERS[2],
                "- 2020年6月10号"
            };

            for (const auto& info : infos) {
                cout << info << "\n";
            }

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

#endif  // __ABOUT_H
