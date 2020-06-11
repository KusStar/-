#pragma once
#ifndef __HISTORY_ITEM_H__
#define __HISTORY_ITEM_H__

#include <string>

class HistoryItem {
public:
    HistoryItem() = default;
    HistoryItem(const std::string& s_index, const std::string& title)
        : index(std::atoi(s_index.c_str())), title(title) {}

    static HistoryItem create(const std::string&, const std::string&);

    size_t index;
    std::string title;
};

inline HistoryItem HistoryItem::create(const std::string& s_index,
                                       const std::string& title) {
    return HistoryItem(s_index, title);
}

#endif  // __HISTORY_ITEM_H__
