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

    //! �������� ��������� �������� ��������� ������
    //! \return ���������� ��������� �������� ��������� ������
    const std::string& GetErrorString() const;

    //! ������� ��������� ���������� ������
    //! \param argc ���-�� ����������
    //! \param argv ������ � �����������
    //! \return ���������� true � ������ ������, ����� - false
    bool ParseArgument(int argc, char** argv);

    //! ����� ������ ������ �� �������
    void ReadConsole();

private:
    //! �������� ������� � ������
    //! \param command �������
    void AddCommand(const std::string& command);

    //! ����������� ����������� ������� �� ������� � �������� ������
    void PrintAndClearVector();

    //! ������ ������ � ����
    //! \param s ������, ������� ����� �������� � ����
    void WriteFile(const std::string& s);

private:
    std::string m_ErrorString;
    unsigned int m_BlockCount;
    int m_BlockDepth;
    std::vector<std::string> m_Vector;
    std::optional<std::chrono::system_clock::time_point> m_Time;
};
//-----------------------------------------------------------------------------
