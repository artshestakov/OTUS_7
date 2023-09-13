#include "cmd.h"
#include <iostream>
//-----------------------------------------------------------------------------
cmd::cmd()
    : m_BlockCount(0)
{

}
//-----------------------------------------------------------------------------
cmd::~cmd()
{

}
//-----------------------------------------------------------------------------
const std::string& cmd::GetErrorString() const
{
    return m_ErrorString;
}
//-----------------------------------------------------------------------------
bool cmd::ParseArgument(int argc, char** argv)
{
    if (argc <= 1)
    {
        m_ErrorString = "You didn't specify an argument";
        return false;
    }

    std::string str = argv[1];
    int n = 0;

    try
    {
        n = std::stoi(str);
    }
    catch (const std::exception& e)
    {
        m_ErrorString = "Can't parse argument '" + str + "': " + std::string(e.what());
        return false;
    }

    if (n <= 0)
    {
        m_ErrorString = "Argument must be greater than zero";
        return false;
    }

    m_BlockCount = (unsigned int)n;
    m_Vector.reserve(m_BlockCount);

    return true;
}
//-----------------------------------------------------------------------------
void cmd::ReadConsole()
{
    std::string command;
    while (std::getline(std::cin, command))
    {
        AddCommand(command);
        if (m_Vector.size() == m_BlockCount || command.empty())
        {
            PrintVector();
            m_Vector.clear();
        }
    }
}
//-----------------------------------------------------------------------------
void cmd::AddCommand(const std::string& command)
{
    if (!command.empty())
    {
        m_Vector.emplace_back(command);
    }
}
//-----------------------------------------------------------------------------
void cmd::PrintVector()
{
    std::cout << "Commands: ";
    for (const std::string& s : m_Vector)
    {
        std::cout << s;
        if (s != m_Vector.back())
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}
//-----------------------------------------------------------------------------
