#include <iostream>
#include <string>
#include "Copy_Tool.h"

int main()
{
    CopyTool copytool("source.txt", "target.txt");
    copytool.start();
    return 0;
}

