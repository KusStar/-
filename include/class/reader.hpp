#pragma once
#ifndef __READER_H__
#define __READER_H__

#include <string>
#include <vector>

#include "file_helper.hpp"
#include "history_item.hpp"

class Reader : public FileHelper {
public:
    Reader() : ok_(false) {}
    ~Reader() { fin_.close(); }

    void init() override;

    std::vector<HistoryItem> get_all();

private:
    std::ifstream fin_;
    bool ok_;
};

inline void Reader::init() {
    if (!ok_) {
        fin_ = std::ifstream(FILE_NAME, std::ios_base::in);
        ok_ = fin_.is_open();
    }
}

inline std::vector<HistoryItem> Reader::get_all() {
    init();
    std::vector<HistoryItem> items;

    if (!ok_)
        return items;

    for (std::string index, name; fin_.good();) {
        fin_ >> index >> name;
        if (!fin_.fail()) {
            items.push_back(HistoryItem::create(index, name));
        }
    }

    std::reverse(items.begin(), items.end());
    return items;
}

#endif  // __READER_H__
