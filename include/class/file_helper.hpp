#pragma once
#ifndef __FILE_HELPER_H__
#define __FILE_HELPER_H__

#include <fstream>
#include <string>

class FileHelper {
public:
    virtual ~FileHelper() = default;
    FileHelper() = default;
    FileHelper(const FileHelper&) = default;
    FileHelper& operator=(const FileHelper&) = default;
    FileHelper(FileHelper&&) = default;
    FileHelper& operator=(FileHelper&&) = default;

    virtual void init() = 0;
    void clear(const std::string&);

protected:
    static const std::string FILE_NAME;
};

inline void FileHelper::clear(const std::string& file_name = FILE_NAME) {
    std::ofstream fout(file_name, std::ios_base::out);
}

const std::string FileHelper::FILE_NAME = "data.txt";

#endif  // __FILE_HELPER_H__
