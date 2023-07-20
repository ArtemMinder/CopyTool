#include <iostream>
#include <string>
#include "Copy_Tool.h"

int main(int argc, char* argv[])
{
    CopyTool copytool(argv[1], argv[2]);
    copytool.start();
    return 0;
}

