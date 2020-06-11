#pragma once
#ifndef __HELP_H
#define __HELP_H

#include "basic.hpp"

namespace wei {
    namespace impls {

        inline void help() {
            using namespace symbols;
            using namespace constants;
            using detail::bright_str;

            const string SPACE = " ";
            const string T = RADIO_OFF + SPACE;
            const string P = RADIO_ON + SPACE;

            cout << "\n  " << bright_str("[帮助]", Attribute::Cyan) << "\n";

            const std::vector<string> tips = {

                bright_str(T + "主界面"),
                P + "键盘<方向键> -> 切换选项",
                P + "键盘<ENTER> -> 确认选项",
                bright_str(T + EXPLORE),
                P + "键盘<j><左>/<k><右> -> 往上/下切换一首诗",
                P + "键盘<h><上>/<l><下> -> 往上/下切换十首诗",
                P + "键盘<ESC><q> -> 返回",
                bright_str(T + SEARCH),
                P + "键盘<英文字符> -> 输入检索关键词（拼音）",
                P + "键盘<上>/<下> -> 切换选项",
                P + "键盘<左>/<右> -> 切换分页",
                P + "键盘<ENTER> -> 查看该诗，之后操作与 [" + EXPLORE +
                    "] 一致",
                P + "键盘<ESC> -> 返回",
                bright_str(T + HISTORY),
                P + "键盘<j><上>/<k><下> -> 切换选项",
                P + "键盘<<h><左>/<l><右> -> 切换分页",
                P + "键盘<x> -> 清除记录",
                P + "键盘<ENTER> -> 查看该诗，之后操作与 [" + EXPLORE + P +
                    "键盘<ESC><q> -> 返回",
            };

            for (const auto& tip : tips) {
                cout << tip << "\n";
            }

            cout << "\n"
                 << bright_str("x", Attribute::Red) << " <q> 返回上一页 ";

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
                            c = std::tolower(c);
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
                                cout << "\n\n";
                                return;
                        }
                        break;
                }
            }
        }

    }  // namespace impls

}  // namespace wei

#endif  // __HELP_H
