#pragma once
#include <iostream>
#include <plog/Util.h>

namespace plog
{
    template<class Formatter>
    class ConsoleAppender : public IAppender
    {
    public:
        ConsoleAppender()
        {
#ifdef _WIN32
            ::setlocale(LC_ALL, "");
#endif
        }

        virtual void write(const Record& record)
        {
            util::nstring str = Formatter::format(record);
            util::MutexLock lock(m_mutex);

            writestr(str);
        }

    protected:
        void writestr(const util::nstring& str)
        {
#ifdef _WIN32
            std::wcout << str << std::flush;
#else
            std::cout << str << std::flush;
#endif
        }

    protected:
        util::Mutex m_mutex;
    };
}
