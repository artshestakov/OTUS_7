#include "cmd.h"
#include <iostream>
#include <sstream>
#include <filesystem>
#include <fstream>
//-----------------------------------------------------------------------------
cmd::cmd()
    : m_BlockCount(0),
    m_BlockDepth(0)
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
    std::cout << "Enter the \"\\q\" command for exit." << std::endl << std::endl;

    std::string command;
    while (std::getline(std::cin, command))
    {
        if (command == "{")
        {
            if (!m_Vector.empty() && m_BlockDepth == 0)
            {
                PrintAndClearVector();
            }

            ++m_BlockDepth;
            continue; //Не допускаем лишней проверки внизу цикла
        }
        else if (command == "}")
        {
            --m_BlockDepth;
            if (m_BlockDepth == 0)
            {
                PrintAndClearVector();
            }
            continue; //Не допускаем лишней проверки внизу цикла
        }
        else if (m_BlockDepth > 0 && command.empty())
        {
            PrintAndClearVector();
            m_BlockDepth = 0;
            continue; //Не допускаем лишней проверки внизу цикла
        }
        else if (command == "\\q") //Не забываем про корректный выход из программы
        {
            std::cout << "The program will be closed" << std::endl;
            break;
        }
        else //Считаем что пришла стандартная команда
        {
            AddCommand(command);
        }

        if (m_BlockDepth == 0 && (m_Vector.size() == m_BlockCount || command.empty()))
        {
            PrintAndClearVector();
        }
    }
}
//-----------------------------------------------------------------------------
void cmd::AddCommand(const std::string& command)
{
    if (!command.empty())
    {
        m_Vector.emplace_back(command);

        if (!m_Time.has_value())
        {
            m_Time = std::chrono::system_clock::now();
        }
    }
}
//-----------------------------------------------------------------------------
void cmd::PrintAndClearVector()
{
    std::stringstream str_stream;

    str_stream << "bulk: ";
    for (const std::string& s : m_Vector)
    {
        str_stream << s;
        if (s != m_Vector.back())
        {
            str_stream << ", ";
        }
    }
    str_stream << std::endl;

    std::string str = str_stream.str();

    std::cout << str;
    WriteFile(str);

    m_Vector.clear();
    m_Time = std::nullopt;
}
//-----------------------------------------------------------------------------
void cmd::WriteFile(const std::string& s)
{
    auto time_sec = std::chrono::duration_cast<std::chrono::seconds>(m_Time.value().time_since_epoch());

    std::string file_name = "bulk" + std::to_string(time_sec.count()) + ".log";
    std::ofstream file(file_name);
    if (!file.is_open())
    {
        std::cout << "Can't write file " + file_name;
        return;
    }

    file << s;
    file.close();
}
//-----------------------------------------------------------------------------
