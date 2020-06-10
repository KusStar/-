#pragma once
#ifndef __POEM_H__
#define __POEM_H__

#include <string>
#include <vector>

#include "jute.h"

class Poem {
    typedef std::string String;
    typedef std::vector<String> Content;

public:
    Poem(const String& title, const String& chapter, const String& section,
         const Content& content, const String& pinyin_title,
         const String& pinyin_content)
        : title(title),
          chapter(chapter),
          section(section),
          content(content),
          pinyin_title(pinyin_title),
          pinyin_content(pinyin_content) {}

    static Poem create(jute::jValue cur);

    String title;
    String chapter;
    String section;
    String pinyin_title;
    String pinyin_content;
    Content content;
};

inline Poem Poem::create(jute::jValue cur) {
    using std::move;
    using std::string;
    using std::vector;

    auto get_content = [](jute::jValue cur_content) {
        vector<string> content;
        for (std::size_t i = 0; i < cur_content.size(); i++) {
            string line = cur_content[i].as_string();
            content.push_back(move(line));
        }
        return content;
    };

    const string title = cur["title"].as_string();
    const string chapter = cur["chapter"].as_string();
    const string section = cur["section"].as_string();
    const string pinyin_title = cur["pinyin"]["title"].as_string();
    const string pinyin_content = cur["pinyin"]["content"].as_string();
    const vector<string> content = get_content(cur["content"]);

    return Poem(move(title), move(chapter), move(section), move(content),
                move(pinyin_title), move(pinyin_content));
}

#endif  // __POEM_H__
