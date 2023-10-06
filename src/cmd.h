#pragma once
//-----------------------------------------------------------------------------
#include "observer.h"
#include "writers.h"
//-----------------------------------------------------------------------------
class cmd : public Observable
{
public:
    cmd();
    ~cmd();

    //! Подписка на события
    //! \param object подписчик
    void Subscribe(Observer* object) override;

    //! Получить текстовое описание последней ошибки
    //! \return возвращает текстовое описание последней ошибки
    const std::string& GetErrorString() const;

    //! Парсинг аргумента конмандной строки
    //! \param argc кол-во аргументов
    //! \param argv массив с аргументами
    //! \return возвращает true в случае успеха, иначе - false
    bool ParseArgument(int argc, char** argv);

    //! Режим чтения данных из консоли
    void ReadConsole();

private:
    //! Добавить команду в память
    //! \param command команда
    void AddCommand(const std::string& command);

    //! Распечатать накопленные команды на консоль и очистить память
    void PrintAndClearVector();

    //! Издать сигнал
    //! \param s строка
    void Notify(const std::string& s);

private:
    std::string m_ErrorString;
    unsigned int m_BlockCount;
    int m_BlockDepth;
    std::vector<std::string> m_Vector;
    std::optional<std::chrono::system_clock::time_point> m_Time;
    std::vector<Observer*> m_Subscribers;
};
//-----------------------------------------------------------------------------
