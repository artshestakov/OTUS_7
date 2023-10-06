#include "writers.h"
//-----------------------------------------------------------------------------
WriterFile::WriterFile(Observable* c)
{
    c->Subscribe(this);
}
//-----------------------------------------------------------------------------
void WriterFile::Update(const std::string& s, const std::chrono::system_clock::time_point& t)
{
    auto time_sec = std::chrono::duration_cast<std::chrono::seconds>(t.time_since_epoch());

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
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
WriterConsole::WriterConsole(Observable* c)
{
    c->Subscribe(this);
}
//-----------------------------------------------------------------------------
void WriterConsole::Update(const std::string& s, const std::chrono::system_clock::time_point& t)
{
    (void)t;
    std::cout << s << std::endl;
}
//-----------------------------------------------------------------------------
