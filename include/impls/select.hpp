#pragma once
#ifndef __SELECT_H
#define __SELECT_H

#include "basic.hpp"

namespace wei {
    namespace impls {

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

    }  // namespace impls

}  // namespace wei


#endif // __SELECT_H
