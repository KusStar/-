#include <iostream>

#include "utils.hpp"
#include "wei.hpp"

using namespace std;

using namespace wei::impls;
using namespace wei::constants;
using wei::Poems;
using wei::select_options;

void run(const Poems& poems) {
    select_options options = {
        EXPLORE, SEARCH, HISTORY, HELP, QUIT,
    };

    for (;;) {
        string res = select(APP_NAME, options);

        if (res == EXPLORE) {
            show(poems);
        }

        if (res == SEARCH) {
            search(poems);
            cout << "\n\n";
        }

        if (res == HISTORY) {
            cout << "\n\n";
        }

        if (res == HELP) {
            help();
        }

        if (res == QUIT) {
            exit(0);
        }
    }
}

int main() {
    bool is_handle_console_success = HandleConsole();
    if (!is_handle_console_success) {
        return 0;
    }

    cout << "载入数据中……"
         << "\n";

    Poems poems = loadData();

    cout << escaper::erase::lines(1) << "载入成功……"
         << "\n";

    run(poems);

    return 0;
}
