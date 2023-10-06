#include "cmd.h"
//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
    cmd c;

    WriterConsole writer_console(&c);
    WriterFile writer_file(&c);

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
