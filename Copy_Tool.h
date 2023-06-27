#pragma once
#include "Reader.h"
#include "Writer.h"
#include "Thread-safe_queue.h"
#include <string>
#include <atomic>

class CopyTool
{
public:
    CopyTool() = delete;
    CopyTool(const std::string& sourceFile, const std::string& targetFile);
    CopyTool(const CopyTool&) = delete;
    CopyTool(CopyTool&&) = delete;
    CopyTool& operator=(const CopyTool&) = delete;
    CopyTool& operator=(CopyTool&&) = delete;
    ~CopyTool() = default;

    void start();
 
private:
    void read();
    void copy();

    Reader _reader;
    Writer _writer;

    TSQueue<std::vector<char>> _data;
    std::atomic<bool> _isRead = false;
};
