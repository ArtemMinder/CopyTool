#include "Thread-safe_queue.h"
#include "Copy_Tool.h"
#include "Reader.h"
#include "Writer.h"
#include <thread>


CopyTool::CopyTool(const std::string& sourceFile, const std::string& targetFile)
{
    _reader.open(sourceFile);
    _writer.open(targetFile);
}

void CopyTool::start()
{
    std::thread readThread(&CopyTool::read, this);
    std::thread copyThread(&CopyTool::copy, this);

    readThread.join();
    copyThread.join();
}

void CopyTool::read()
{
    while (!_reader.isEndOfFile())
    {
        _data.push(_reader.read());
    }
    _isRead = true;
}

void CopyTool::copy()
{
    while (!_isRead)
    {      
        _writer.write(_data.pop());
    }

    while (!_data.empty())
    {
        _writer.write(_data.pop());
    }
}

