#include <iostream>

#include "wei.hpp"

using namespace wei::impls;
using namespace escaper;
using namespace std;
using wei::select_options;

int main() {
    bool is_handle_console_success = HandleConsole();
    if (!is_handle_console_success) {
        return 0;
    }

    cout << "载入数据中……"
         << "\n";

    jute::jValue v = loadData();

    cout << erase::lines(1) << "载入成功……"
         << "\n\n";

    select_options options = {"诗经", "搜索", "历史", "帮助", "退出"};

    for (;;) {
        string res = select(APP_NAME, options);

        if (res == options[0]) {
            show_all(v);
        }

        if (res == options[1]) {
            search();
            cout << "\n\n";
        }

        if (res == options[2]) {
            cout << "\n\n";
        }

        if (res == options[3]) {
            help();
        }

        if (res == options[4]) {
            break;
        }
    }

    return 0;
}
