#pragma once
#include <exception>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>

class Reader
{
public:
    Reader() = default;
    Reader(const std::string& path)
    {
        open(path);
    }
    Reader(const Reader&) = delete;
    Reader(Reader&&) = delete;
    Reader& operator=(const Reader&) = delete;
    Reader& operator=(Reader&&) = delete;

    ~Reader()
    {
        if (_source)
            _source.close();
    }

    void open(const std::string& path)
    {
        _source.open(path, std::ios_base::binary);
        if (!_source)
            throw std::runtime_error("Source file not found");
    }

    std::vector<char> read()
    {
        std::vector<char> buffer(1048576, '\0');
        _source.read(buffer.data(), 1048576);
        const size_t actual = _source.gcount();
        buffer.resize(actual + 1);
        return buffer;
    }

    void close() 
    { 
        _source.close(); 
    }

    bool isEndOfFile() const
    { 
        return _source.eof(); 
    }

private:
    std::ifstream _source;
};