#pragma once
#ifndef __WRITER_H__
#define __WRITER_H__

#include "file_helper.hpp"
#include "poem.hpp"

class Writer : public FileHelper {
public:
    Writer() : ok_(false) {}
    ~Writer() { fout_.close(); }

    void init() override;
    void put(const size_t, const std::string&);

private:
    std::ofstream fout_;
    bool ok_;
};

inline void Writer::init() {
    if (!ok_) {
        fout_ = std::ofstream(FILE_NAME, std::ios::app);
        ok_ = fout_.is_open();
    }
}

inline void Writer::put(const size_t index, const std::string& name) {
    init();

    if (ok_) {
        fout_ << index << " " << name << '\n';
    }
}

#endif  // __WRITER_H__
