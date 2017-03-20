#pragma once

namespace plog
{
    template<class Formatter>
    class DebugOutputAppender : public IAppender
    {
    public:
        virtual void write(const Record& record)
        {
            ::OutputDebugStringW(Formatter::format(record).c_str());
        }
    };
}
