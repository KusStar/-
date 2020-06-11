#pragma once
#ifndef __SELECT_H
#define __SELECT_H

#include "basic.hpp"

namespace wei {
    namespace impls {

        inline string select(const string& message,
                             const select_options& options, int& index) {
            Brush brush;

            int len = options.size();

            cout << detail::title_str(message, symbols::APP_ICON) << "\n";

            for (;;) {
                for (int i = 0; i < len; i++) {
                    string option_str =
                        detail::mark_str(index, i) + " " + options.at(i);
                    brush << option_str << "\n";
                }

                brush.draw();

                int c = getch();

                switch (c) {
                    case KEY_ENTER:
                    case KEY_SPACE:
                        return options.at(index);
                    case KEY_ESC:
                        return options.at(options.size() - 1);
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
                                cout << "\n";
                                return options.at(len - 1);
                        }
                        break;
                }
                brush.flush();
            }
        }

    }  // namespace impls

}  // namespace wei

#endif  // __SELECT_H
