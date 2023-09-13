#include "cmd.h"
#include <iostream>
//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
    cmd c;

    //Парсим аргумент
    if (!c.ParseArgument(argc, argv))
    {
        std::cout << c.GetErrorString() << std::endl;
        return 1;
    }

    //Вызываем режим чтения консоли
    c.ReadConsole();

    return 0;
}
//-----------------------------------------------------------------------------
