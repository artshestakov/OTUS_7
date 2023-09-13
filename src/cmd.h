#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <vector>
#include <chrono>
#include <optional>
//-----------------------------------------------------------------------------
class cmd
{
public:
    cmd();
    ~cmd();

    //! ѕолучить текстовое описание последней ошибки
    //! \return возвращает текстовое описание последней ошибки
    const std::string& GetErrorString() const;

    //! ѕарсинг аргумента конмандной строки
    //! \param argc кол-во аргументов
    //! \param argv массив с аргументами
    //! \return возвращает true в случае успеха, иначе - false
    bool ParseArgument(int argc, char** argv);

    //! –ежим чтени€ данных из консоли
    void ReadConsole();

private:
    //! ƒобавить команду в пам€ть
    //! \param command команда
    void AddCommand(const std::string& command);

    //! –аспечатать накопленные команды на консоль и очистить пам€ть
    void PrintAndClearVector();

    //! «апись строки в файл
    //! \param s строка, котора€ будет записана в файл
    void WriteFile(const std::string& s);

private:
    std::string m_ErrorString;
    unsigned int m_BlockCount;
    int m_BlockDepth;
    std::vector<std::string> m_Vector;
    std::optional<std::chrono::system_clock::time_point> m_Time;
};
//-----------------------------------------------------------------------------
