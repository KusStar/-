#pragma once
#ifndef __WEI_H__
#define __WEI_H__

#include "basic.hpp"

#include "impls/search.hpp"
#include "impls/select.hpp"
#include "impls/show.hpp"

namespace wei {
    namespace impls {
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

    }  // namespace impls

}  // namespace wei

#endif // __WEI_H__
