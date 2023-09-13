#include "cmd.h"
#include <iostream>
//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
    cmd c;

    //������ ��������
    if (!c.ParseArgument(argc, argv))
    {
        std::cout << c.GetErrorString() << std::endl;
        return 1;
    }

    //�������� ����� ������ �������
    c.ReadConsole();

    return 0;
}
//-----------------------------------------------------------------------------
